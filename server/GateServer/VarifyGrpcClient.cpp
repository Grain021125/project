#include "VarifyGrpcClient.h"
#include "ConfigMgr.h"

VarifyGrpcClient::VarifyGrpcClient()
{
	auto& configMgr = ConfigMgr::GetInstance();
	std::string host = configMgr["VarifyServer"]["Host"];
	std::string port = configMgr["VarifyServer"]["Port"];
	_pool.reset(new RpcConnetionPool(5, host, port));
}