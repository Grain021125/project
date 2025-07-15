#include "CServer.h"
#include "HttpConnection.h"

CServer::CServer(net::io_context& ioc, unsigned short& port): 
	_ioc(ioc), _acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _socket(ioc)
{

}

void CServer::Start() {
	auto self = shared_from_this();
	_acceptor.async_accept(_socket, [self](beast::error_code ec) {
		try
		{
			//出错放弃链接,继续监听其他链接
			if (ec) {
				self->Start();
				return;
			}
			//创建新链接,并且创建HttpConnection类管理这个链接
			std::make_shared<HttpConnection>(std::move(self->_socket))->Start();

			self->Start();
		}
		catch (const std::exception& exp)
		{

		}
		}); //把接受到的链接传递给socket
}
