#include "LogicSystem.h"
#include "StatusGrpcClient.h"
#include "MysqlMgr.h"
#include "RedisMgr.h"

LogicSystem::LogicSystem(): _b_stop(false)
{
	RegisterCallBacks();
	_worker_thread = std::thread([this]() {
		DealMsg();
		});
}

void LogicSystem::RegisterCallBacks()
{
	// 注册登录处理函数
	_fun_callbacks[MSG_CHAT_LOGIN] = std::bind(&LogicSystem::LoginHandler, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

void LogicSystem::LoginHandler(std::shared_ptr<CSession> session, const short& msg_id, const std::string& msg_data)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	auto uid = root["uid"].asInt();
	std::cout << "LoginHandler called with uid: " << uid << ", user token: " << root["token"].asString() << std::endl;
	// 从状态服务器获取token匹配是否准确
	auto rsp = StatusGrpcClient::GetInstance()->Login(uid, root["token"].asString());
	Json::Value rsp_root;
	Defer defer([this, &rsp_root, session]() {
		std::string return_str = rsp_root.toStyledString();
		session->AsyncSend(return_str.c_str(), MSG_CHAT_LOGIN_RSP, return_str.length());
		});

	rsp_root["error"] = rsp.error();
	if (rsp.error() != ErrorCodes::SUCCESS) {
		std::cout << "Login failed with error code: " << rsp.error() << std::endl;
		return;
	}

	//内存中查询用户信息
	auto find_iter = _users.find(uid);
	std::shared_ptr<UserInfo> user_info;
	if (find_iter == _users.end()) {
		//查询数据库
		user_info = std::make_shared<UserInfo>(MysqlMgr::GetInstance()->GetUser(uid));
		if (user_info == nullptr) {
			rsp_root["error"] = ErrorCodes::UID_INVALID;
			return;
		}

		_users[uid] = user_info;
	}
	else {
		user_info = find_iter->second;
	}

	rsp_root["uid"] = uid;
	rsp_root["token"] = rsp.token();
	rsp_root["name"] = user_info->name;
}

LogicSystem::~LogicSystem()
{
	_b_stop = true;
	_consume.notify_one(); // 唤醒处理线程以便它可以退出
	_worker_thread.join();
}

void LogicSystem::PostMsgToQue(std::shared_ptr<LogicNode> msg)
{
	std::unique_lock<std::mutex> lock(_mutex);
	_msg_queue.push(msg);
	if (_msg_queue.size() == 1) {
		// 如果队列中只有一个元素，表示需要处理的消息
		lock.unlock();
		// 这里可以使用条件变量来唤醒处理线程
		_consume.notify_one();
	}
}

void LogicSystem::DealMsg()
{
	for (;;) {
		std::unique_lock<std::mutex> lock(_mutex);
		while (_msg_queue.empty() && !_b_stop) {
			_consume.wait(lock); // 等待直到有消息到来或停止信号
		}

		// 如果接收到停止信号，处理完所有消息后退出循环
		if (_b_stop) {
			while (!_msg_queue.empty()) {
				auto msg_node = _msg_queue.front();
				std::cout << "recv msg node is " << msg_node->_msg_node->_msg_id << std::endl;
				auto call_back_iter = _fun_callbacks.find(msg_node->_msg_node->_msg_id);
				if(call_back_iter == _fun_callbacks.end()) {
					std::cout << "No callback found for msg_id: " << msg_node->_msg_node->_msg_id << std::endl;
					continue;
				}
				call_back_iter->second(msg_node->_session, msg_node->_msg_node->_msg_id, 
					std::string(msg_node->_msg_node->_data, msg_node->_msg_node->_cur_len));
				_msg_queue.pop();
			}
			break; // 退出循环
		}

		// 处理消息
		auto msg_node = _msg_queue.front();
		std::cout << "recv msg node is " << msg_node->_msg_node->_msg_id << std::endl;
		auto call_back_iter = _fun_callbacks.find(msg_node->_msg_node->_msg_id);
		if (call_back_iter == _fun_callbacks.end()) {
			std::cout << "No callback found for msg_id: " << msg_node->_msg_node->_msg_id << std::endl;
			_msg_queue.pop();
			continue; // 如果没有找到对应的回调函数，跳过当前消息
		}
		call_back_iter->second(msg_node->_session, msg_node->_msg_node->_msg_id, 
			std::string(msg_node->_msg_node->_data, msg_node->_msg_node->_cur_len));
		_msg_queue.pop();
	}
}

