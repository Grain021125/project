#pragma once
#include "message.grpc.pb.h"
#include "message.pb.h"
#include <grpcpp/grpcpp.h>
#include "Singleton.h"
#include "ConfigMgr.h"
#include "const.h"
#include "data.h"
#include <queue>
#include <string>
#include <memory>
#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::AddFriendReq;
using message::AddFriendRsp;

using message::AuthFriendReq;
using message::AuthFriendRsp;

using message::GetChatServerRsp;
using message::LoginRsp;
using message::LoginReq;
using message::ChatService;

using message::TextChatMsgReq;
using message::TextChatMsgRsp;
using message::TextChatData;

//using message::KickUserReq;
//using message::KickUserRsp;


class ChatConPool {
public:
	ChatConPool(size_t pool_size, const std::string& host, const std::string& port):
		_pool_size(pool_size), _host(host), _port(port), _b_stop(false) { 
		for (size_t i = 0; i < _pool_size; ++i) {
			auto channel = grpc::CreateChannel(_host + ":" + _port, grpc::InsecureChannelCredentials());
			auto stub = ChatService::NewStub(channel);
			_connections.push(std::move(stub));
		}
	 }

	~ChatConPool()
	{
		std::lock_guard<std::mutex> lock(_mutex);
		Close();
		while (!_connections.empty()) {
			_connections.pop();
		}
	}

	void Close() {
		_b_stop = true;
		_cond.notify_all();
	}

	std::unique_ptr<ChatService::Stub> getConnection() {
		std::unique_lock<std::mutex> lock(_mutex);
		_cond.wait(lock, [this] {
			if (_b_stop) return true;
			return !_connections.empty();
			});
		if (_b_stop) {
			return nullptr;
		}
		auto context = std::move(_connections.front());
		_connections.pop();
		return context;
	}

	void returnConnection(std::unique_ptr<ChatService::Stub> stub) {
		std::lock_guard<std::mutex> lock(_mutex);
		if (_b_stop) {
			return;
		}
		_connections.push(std::move(stub));
		_cond.notify_one();
	}

private:
	std::atomic<bool> _b_stop;
	size_t _pool_size;
	std::string _host;
	std::string _port;
	std::queue<std::unique_ptr<ChatService::Stub> > _connections;
	std::mutex _mutex;
	std::condition_variable _cond;
};

class ChatGrpcClient : public Singleton<ChatGrpcClient>
{
	friend class Singleton<ChatGrpcClient>;
public:
	~ChatGrpcClient()
	{

	}

	AddFriendRsp NotifyAddFriend(std::string server_ip, const AddFriendReq& req);
	AuthFriendRsp NotifyAuthFriend(std::string server_ip, const AuthFriendReq& req);
	bool GetBaseInfo(const std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo);
	TextChatMsgRsp NotifyTextChatMsg(std::string server_ip, const TextChatMsgReq& req, const Json::Value& rtvalue);

private:
	ChatGrpcClient();
	std::unordered_map<std::string, std::shared_ptr<ChatConPool>> _pools;
};

