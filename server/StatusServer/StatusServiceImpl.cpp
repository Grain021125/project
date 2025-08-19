#include "StatusServiceImpl.h"
#include "ConfigMgr.h"
#include "const.h"
#include "RedisMgr.h"


std::string generate_unique_string() {
    // 创建UUID对象
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    // 将UUID转换为字符串
    std::string unique_string = to_string(uuid);
    return unique_string;
}


StatusServiceImpl::StatusServiceImpl()
{
    auto& cfg = ConfigMgr::GetInstance();
    auto server_list = cfg["ChatServers"]["Name"];

    std::vector<std::string> words;

	std::stringstream ss(server_list);
	std::string word;

    while (std::getline(ss, word, ',')) {
        words.push_back(word);
	}

    for (auto& word: words) {
        if (cfg[word]["Name"].empty()) {
            continue;
        }

		ChatServer server;
		server.host = cfg[word]["Host"];
		server.port = cfg[word]["Port"];
		server.name = cfg[word]["Name"];
        _servers[server.name] = server;
	}
}

ChatServer StatusServiceImpl::getChatServer()
{
    std::lock_guard<std::mutex> lock(_server_mutex);
    if (_servers.empty()) {
        throw std::runtime_error("No chat servers available");
    }

    auto minServer = _servers.begin()->second;

    //TODO: 负载均衡
    return minServer;
}

Status StatusServiceImpl::GetChatServer(ServerContext* context, const GetChatServerReq* request, GetChatServerRsp* reply)
{
    std::string prefix("llfc status server has received :  ");
    auto server = getChatServer();
    reply->set_host(server.host);
    reply->set_port(server.port);
    reply->set_error(ErrorCodes::SUCCESS);
    reply->set_token(generate_unique_string());
    insertToken(request->uid(), reply->token());
    return Status::OK;
}

Status StatusServiceImpl::Login(ServerContext* context, const LoginReq* request, LoginRsp* reply)
{
	auto uid = request->uid();
	auto token = request->token();

	std::string uid_str = std::to_string(uid);
	std::string token_key = USERTOKENPREFIX + uid_str;
    std::string token_value;
	bool success = RedisMgr::GetInstance()->Get(token_key, token_value);

    if (!success) {
        reply->set_error(ErrorCodes::UID_INVALID);
		return Status::OK;
    }

	std::cout << "token key: " << token_key << std::endl;
    std::cout << token << " | " << token_value << std::endl;
	if (token_value != token) {
        reply->set_error(ErrorCodes::TOKEN_INVALID);
        return Status::OK;
    }
    reply->set_error(ErrorCodes::SUCCESS);
    reply->set_uid(uid);
    reply->set_token(token_value);
    return Status::OK;
}

void StatusServiceImpl::insertToken(int uid, const std::string& token)
{
    std::string uid_str = std::to_string(uid);
    std::string token_key = USERTOKENPREFIX + uid_str;
    RedisMgr::GetInstance()->Set(token_key, token);
}