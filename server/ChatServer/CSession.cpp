#include "CSession.h"
#include "CServer.h"
#include <boost/uuid.hpp>
#include "LogicSystem.h"

CSession::CSession(boost::asio::io_context& io_context, CServer* server)
	: _socket(io_context), _server(server), _session_id(boost::uuids::to_string(boost::uuids::random_generator()())), _b_close(false), _b_head_parse(false)
{
	std::cout << "New session created with ID: " << _session_id << std::endl;
}

tcp::socket& CSession::GetSocket()
{
	return _socket;
}

void CSession::Start()
{
	AsyncReadHead(HEAD_TOTAL_LEN);
}

void CSession::Close() {
	std::lock_guard<std::mutex> lock(_mutex);
	if (_b_close) {
		return; // 如果已经关闭，则直接返回
	}
	_b_close = true; // 设置为已关闭状态
	std::cout << "Closing session with ID: " << _session_id << std::endl;
	_socket.close(); // 关闭socket连接
	if (_server) {
		_server->ClearSessions(_session_id); // 通知服务器清除该会话
	}
}

std::string CSession::GetSessionID()
{
	return _session_id;
}

std::string CSession::GetUserId()
{
	return std::string();
}

void CSession::AsyncReadHead(int total_len)
{
	auto self = shared_from_this();

	boost::asio::async_read(_socket, boost::asio::buffer(_head_buffer, total_len), [self, this](const boost::system::error_code& ec, std::size_t bytes_tranfered) {
		try
		{
			if (ec) {
				std::cout << "Error reading header: " << ec.message() << std::endl;
				Close();
				return;
			}

			if (bytes_tranfered != HEAD_TOTAL_LEN) {
				std::cout << "Error: Incomplete header received, expected " << HEAD_TOTAL_LEN << " bytes, got " << bytes_tranfered << " bytes." << std::endl;
				Close(); // TODO:健壮错误处理
				return;
			}

			_recv_head_node->Clear();
			memcpy(_recv_head_node->_data, _head_buffer.data(), bytes_tranfered);

			//解析头部数据: MSG_ID + MSG_LEN
			std::uint16_t msg_id = 0;
			memcpy(&msg_id, _recv_head_node->_data, HEAD_ID_LEN);

			msg_id = ntohs(msg_id); // 转换为主机字节序

			std::cout << "Received header with MSG_ID: " << msg_id << std::endl;

			if (msg_id > MAX_ID_LENGTH) {
				std::cout << "Error: MSG_ID exceeds maximum length." << std::endl;
				Close(); // TODO:健壮错误处理
				return;
			}

			std::uint16_t msg_len = 0;
			memcpy(&msg_len, _recv_head_node->_data + HEAD_ID_LEN, HEAD_DATA_LEN);
			msg_len = ntohs(msg_len); // 转换为主机字节序
			std::cout << "Received header with MSG_LEN: " << msg_len << std::endl;

			if (msg_len >= MAX_DATA_LENGTH) {
				std::cout << "Error: MSG_LEN exceeds maximum data length." << std::endl;
				Close(); // TODO:健壮错误处理
				return;
			}

			_recv_msg_node = std::make_shared<RecvNode>(msg_len, msg_id);

			AsyncReadBody(msg_len);
		}
		catch (const std::exception& e)
		{
			std::cout << "Exception code is " << e.what() << std::endl;
		}
		});
}

void CSession::AsyncReadBody(int total_len)
{
	auto self = shared_from_this();
	boost::asio::async_read(_socket, boost::asio::buffer(_body_buffer, total_len), [self, this, total_len](const boost::system::error_code& ec, std::size_t bytes_tranfered) {
		try
		{
			if (ec) {
				std::cout << "Error reading body: " << ec.message() << std::endl;
				Close();
				return;
			}
			
			if (bytes_tranfered < total_len) {
				std::cout << "Error: Incomplete body received, expected " << total_len << " bytes, got " << bytes_tranfered << " bytes." << std::endl;
				Close(); // TODO:健壮错误处理
				return;
			}

			_recv_head_node = std::make_shared<MsgNode>(total_len);
			memcpy(_recv_msg_node->_data, _body_buffer.data(), bytes_tranfered);
			_recv_msg_node->_cur_len += bytes_tranfered;
			std::cout << "Session with ID " << _session_id << "receive data " << _recv_msg_node->_data << std::endl;

			//将消息投递到逻辑队列中
			LogicSystem::GetInstance()->PostMsgToQue(std::make_shared<LogicNode>(shared_from_this(), _recv_msg_node));

			//继续监听头部
			AsyncReadHead(HEAD_TOTAL_LEN);
		}
		catch (const std::exception& e)
		{
			std::cout << "Exception code is " << e.what() << std::endl;
		}
		});
}

void CSession::AsyncSend(const char* msg, uint16_t msg_id, uint16_t msg_len)
{
	std::lock_guard<std::mutex> lock(_send_mutex);
	auto self = shared_from_this();
	int send_queue_size = _send_queue.size();
	if (send_queue_size >= MAX_SENDQUE_SIZE) {
		std::cout << "Session" << _session_id << "Send queue size exceeds maximum limit: " << send_queue_size << std::endl;
		return; // 队列已满，直接返回
	}

	_send_queue.push_back(std::make_shared<SendNode>(msg, msg_id, msg_len));
	if (send_queue_size > 0) {
		return;
	}

	auto& msgnode = _send_queue.front();
	boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_total_len),
		[this, self](const boost::system::error_code& ec, std::size_t bytes_transfered) {
			HandleSend(ec, self);
		});
}

void CSession::HandleSend(const boost::system::error_code& ec, std::shared_ptr<CSession> shared_self)
{
	try
	{
		if (!ec) {
			std::lock_guard<std::mutex> lock(_send_mutex);
			_send_queue.pop_front(); // 发送成功后移除队列头部的消息
			if (!_send_queue.empty()) {
				auto& msgnode = _send_queue.front();
				boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_total_len),
					[this, shared_self](const boost::system::error_code& ec, std::size_t byte_transfered) {
						HandleSend(ec, shared_self);
					});
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception in HandleSend: " << e.what() << std::endl;
	}
}
