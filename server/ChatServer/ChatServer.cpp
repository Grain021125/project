#include "ConfigMgr.h"
#include "AsioIOServicePool.h"
#include "CServer.h"
#include "CSession.h"

int main()
{
	try
	{
		auto& cfg = ConfigMgr::GetInstance();
		auto pool = AsioIOServicePool::GetInstance();
		boost::asio::io_context io_context;
		boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
		signals.async_wait([&](const boost::system::error_code& error, int signal_number) {
			if (!error) //防止异常信号
			{
				io_context.stop();
				pool->Stop();
			}
			});
		std::string port_str = cfg["SelfServer"]["Port"];
		auto server_ptr = std::make_shared<CServer>(io_context, atoi(port_str.c_str()));
		io_context.run();
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}
}
