#pragma once
#include "Singleton.h"
#include "CSession.h"
#include "const.h"

using  FunCallBack = std::function<void(std::shared_ptr<CSession>, const uint16_t& msg_id, const std::string& msg_data)>;
class LogicSystem : public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>;
public:
	~LogicSystem();
	void PostMsgToQue(std::shared_ptr<LogicNode> msg);
private:
	LogicSystem();
	void RegisterCallBacks();
	void LoginHandler(std::shared_ptr<CSession> session,std::shared_ptr<LogicNode> msg_node);

	std::queue<std::shared_ptr<LogicNode>> _msg_queue; // 存储待处理的消息队列
	std::mutex _mutex; // 保护_fun_callbacks的互斥锁
	bool _b_stop = false;
	std::vector<uint16_t, FunCallBack> _fun_callbacks; // 存储消息ID和对应的处理函数
};

