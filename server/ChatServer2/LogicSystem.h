#pragma once
#include "Singleton.h"
#include "MysqlMgr.h"
#include "CSession.h"
#include "const.h"

using  FunCallBack = std::function<void(std::shared_ptr<CSession>, const uint16_t& msg_id, const std::string& msg_data)>;
class LogicSystem : public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>;
public:
	~LogicSystem();
	void PostMsgToQue(std::shared_ptr<LogicNode> msg);
	void DealMsg();
private:
	LogicSystem();
	void RegisterCallBacks();
	void LoginHandler(std::shared_ptr<CSession> session, const short& msg_id, const std::string& msg_data);

	std::queue<std::shared_ptr<LogicNode>> _msg_queue; // 存储待处理的消息队列
	std::mutex _mutex; // 保护_fun_callbacks的互斥锁
	bool _b_stop = false;
	std::condition_variable _consume; // 条件变量，用于通知处理线程
	std::map<uint16_t, FunCallBack> _fun_callbacks; // 存储消息ID和对应的处理函数
	std::thread _worker_thread; // 处理消息的工作线程
	std::map<int, std::shared_ptr<UserInfo>> _users; // 存储用户信息的映射
};

