#include "AsioIOServicePool.h"

AsioIOServicePool::AsioIOServicePool(std::size_t size) : _ioService(size), _works(size), _nextIOService(0)
{
	//for (std::size_t i = 0; i < size; ++i) {
	//	_works[i] = WorkPtr(new Work(_ioService[i].get_executor()));
	//}

	//遍历多个ioservice，创建多个线程，每个线程内部启动ioservice
	for (std::size_t i = 0; i < size; ++i) {
		_works[i] = WorkPtr(new Work(_ioService[i].get_executor())); //绑定io_service到work对象上，防止io_service在没有任务时被销毁
		_threads.emplace_back([this, i]() {
			_ioService[i].run();
			});
	}
}

AsioIOServicePool::~AsioIOServicePool() {
	Stop();
	std::cout << "AsioIOServicePool destruct" << std::endl;
}

boost::asio::io_context& AsioIOServicePool::GetIOService()
{
	auto& service = _ioService[_nextIOService++];
	if (_nextIOService == _ioService.size()) {
		_nextIOService = 0;
	}

	return service;
}

void AsioIOServicePool::Stop()
{
	for (auto& work : _works) {
		//停止服务
		work->get_executor().context().stop(); //停止io_service的运行
		work.reset(); //释放work对象
	}

	for (auto& t : _threads) {
		t.join();
	}
}

