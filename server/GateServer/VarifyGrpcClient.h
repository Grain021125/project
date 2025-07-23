#pragma once
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "const.h"

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVarifyReq;
using message::GetVarifyRsp;
using message::VarifyService;

class RpcConnetionPool {
public:
	RpcConnetionPool(std::size_t poolsize, std::string host, std::string port):
		_poolsize(poolsize), _host(host), _port(port), _b_stop(false)
	{
		for (std::size_t i = 0; i < poolsize; ++i) {
			std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port, grpc::InsecureChannelCredentials());
			_stubs.push(VarifyService::NewStub(channel));
		}
	}

	~RpcConnetionPool() {
		std::lock_guard<std::mutex> lock(_mutex);
		Stop();
		while(!_stubs.empty()) {
			_stubs.pop();
		}
	}

	void Stop() {
		_b_stop.store(true); // ����ֹͣ��־
		_cond_var.notify_all(); 
	}

	std::unique_ptr<VarifyService::Stub> getConnection() {
		std::unique_lock<std::mutex> lock(_mutex);
		_cond_var.wait(lock, [this]() {
			if (_b_stop) 
				return true; // ���ֹͣ��־�����ã�ֱ�ӷ���

			return !_stubs.empty(); // �ȴ�ֱ��_stubs���в�Ϊ��
			});

		if (_b_stop) {
			return nullptr; // ���ֹͣ��־�����ã�����nullptr
		}

		auto stub = std::move(_stubs.front());
		_stubs.pop(); // �Ӷ������Ƴ�ǰ�˵�Stub
		return stub; // ��ȡ����ǰ�˵�Stub
	}

	void returnConnection(std::unique_ptr<VarifyService::Stub> stub) {
		std::lock_guard<std::mutex> lock(_mutex);
		if (_b_stop) {
			return; // ���ֹͣ��־�����ã�ֱ�ӷ���
		}
		_stubs.push(std::move(stub)); // ��Stub�Żض���
		_cond_var.notify_one(); // ֪ͨһ���ȴ����߳�
	}

private:
	std::atomic<bool> _b_stop;
	std::size_t _poolsize;
	std::string _host;
	std::string _port;
	std::queue<std::unique_ptr<VarifyService::Stub>> _stubs;
	std::mutex _mutex; // ���ڱ���_stubs���еĻ�����
	std::condition_variable _cond_var; // ����֪ͨ�ȴ����߳�
};

class VarifyGrpcClient : public Singleton<VarifyGrpcClient>
{
	friend class Singleton<VarifyGrpcClient>;
public:
	GetVarifyRsp GetVarifyCode(std::string email) {
		ClientContext context;
		GetVarifyRsp reply;
		GetVarifyReq request;
		auto _stub = _pool->getConnection();
		request.set_email(email);

		Status status = _stub->GetVarifyCode(&context, request, &reply);
		if (status.ok()) {
			_pool->returnConnection(std::move(_stub));
			return reply;
		}
		else {
			_pool->returnConnection(std::move(_stub));
			reply.set_error(ErrorCodes::RPCFailed);
			return reply;
		}
	}

private:
	VarifyGrpcClient();

	std::unique_ptr<RpcConnetionPool> _pool;
};

