#include "AsioIOServicePool.h"

AsioIOServicePool::AsioIOServicePool(std::size_t size) : _ioService(size), _works(size), _nextIOService(0)
{
	//for (std::size_t i = 0; i < size; ++i) {
	//	_works[i] = WorkPtr(new Work(_ioService[i].get_executor()));
	//}

	//�������ioservice����������̣߳�ÿ���߳��ڲ�����ioservice
	for (std::size_t i = 0; i < size; ++i) {
		_works[i] = WorkPtr(new Work(_ioService[i].get_executor())); //��io_service��work�����ϣ���ֹio_service��û������ʱ������
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
		//ֹͣ����
		work->get_executor().context().stop(); //ֹͣio_service������
		work.reset(); //�ͷ�work����
	}

	for (auto& t : _threads) {
		t.join();
	}
}

