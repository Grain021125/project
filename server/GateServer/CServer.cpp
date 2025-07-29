#include "CServer.h"
#include "HttpConnection.h"
#include "AsioIOServicePool.h"

CServer::CServer(net::io_context& ioc, unsigned short& port): 
	_ioc(ioc), _acceptor(ioc, tcp::endpoint(tcp::v4(), port))
{

}

void CServer::Start() {
	auto self = shared_from_this();
	boost::asio::io_context& ioc = AsioIOServicePool::GetInstance()->GetIOService();
	std::shared_ptr<HttpConnection> connection = std::make_shared<HttpConnection>(ioc);
	_acceptor.async_accept(connection->GetSocket(), [self, connection](beast::error_code ec) {
		try
		{
			//出错放弃链接,继续监听其他链接
			if (ec) {
				self->Start();
				return;
			}
			connection->Start();

			self->Start();
		}
		catch (const std::exception& exp)
		{
			std::cerr << "CServer::Start exception: " << exp.what() << std::endl;
		}
		}); //把接受到的链接传递给socket
}
