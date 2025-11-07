#include "ChatGrpcClient.h"
#include "string"

#include "RedisMgr.h"
#include "ConfigMgr.h"


#include "CSession.h"
#include "MysqlMgr.h"

AddFriendRsp ChatGrpcClient::NotifyAddFriend(std::string server_ip, const AddFriendReq& req)
{
    return AddFriendRsp();
}

AuthFriendRsp ChatGrpcClient::NotifyAuthFriend(std::string server_ip, const AuthFriendReq& req)
{
    return AuthFriendRsp();
}

bool ChatGrpcClient::GetBaseInfo(const std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo)
{
    return true;
}
  

TextChatMsgRsp ChatGrpcClient::NotifyTextChatMsg(std::string server_ip, const TextChatMsgReq& req, const Json::Value& rtvalue)
{
    return TextChatMsgRsp();
}
