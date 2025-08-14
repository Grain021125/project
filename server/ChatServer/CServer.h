#pragma once
#include <mutex>
#include <map>
#include <memory.h>
#include <boost/asio.hpp>
#include <iostream>
#include "CSession.h"
#include "AsioIOServicePool.h"

using boost::asio::ip::tcp;

class CServer: public std::enable_shared_from_this<CServer>
{
public:
	CServer(boost::asio::io_context& io_context, short port);
	~CServer();
	void ClearSessions(std::string);
private:
	void HandleAccept(std::shared_ptr<CSession> session, const boost::system::error_code& error);
	void StartAccept();

	boost::asio::io_context& _io_context;
	short _port;
	tcp::acceptor _acceptor;
	std::map<std::string, std::shared_ptr<CSession>> _sessions; //存储所有连接的会话
	std::mutex _mutex; //保护_sessions的互斥锁
};

