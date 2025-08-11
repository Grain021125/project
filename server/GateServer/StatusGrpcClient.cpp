#include "StatusGrpcClient.h"

GetChatServerRsp StatusGrpcClient::GetChatServer(int uid)
{
	ClientContext context;
	GetChatServerReq request;
	GetChatServerRsp response;
	request.set_uid(uid);
	auto stub = _pool->getConnection();
	Status status = stub->GetChatServer(&context, request, &response);
	Defer defer([this, &stub]() {
		_pool->returnConnection(std::move(stub));
		});

	if (!status.ok()) {
		response.set_error(ErrorCodes::RPC_FAILD);
		return response;
	}
    return response;
}

StatusGrpcClient::StatusGrpcClient()
{
	auto& cfg = ConfigMgr::GetInstance();
	std::string host = cfg["StatusServer"]["Host"];
	std::string port = cfg["StatusServer"]["Port"];
	_pool.reset(new StatusConPool(5, host, port));
}
