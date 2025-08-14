#include "CServer.h"

CServer::CServer(boost::asio::io_context& io_context, short port):
	_io_context(io_context), _port(port), _acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{
	std::cout << "Server start success, listen on port: " << _port << std::endl;
	StartAccept();
}

CServer::~CServer()
{
	std::cout << "Server stop" << std::endl;
}

void CServer::StartAccept() {
	auto self = shared_from_this();
	boost::asio::io_context& io_context = AsioIOServicePool::GetInstance()->GetIOService();
	std::shared_ptr<CSession> session = std::make_shared<CSession>(io_context, this); // 使用shared_from_this确保CServer对象在异步操作期间不会被销毁
	_acceptor.async_accept(session->GetSocket(),
		[self, session](const boost::system::error_code& ec) {
			self->HandleAccept(
				session, 
				ec
			);
		}
		);
}

void CServer::HandleAccept(std::shared_ptr<CSession> session, const boost::system::error_code& error) {
	if (!error) {
		std::cout << "New connection accepted" << std::endl;
		session->Start();
		std::lock_guard<std::mutex> lock(_mutex);
		_sessions.insert(std::make_pair(session->GetUuid(), session));
	}
	else {
		std::cerr << "Error on accept: " << error.what() << std::endl;
	}

	StartAccept();
}
