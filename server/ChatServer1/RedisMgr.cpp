#include "RedisMgr.h"

RedisMgr::RedisMgr()
{
	auto& configMgr = ConfigMgr::GetInstance();
	auto host = configMgr["RedisServer"]["Host"];
	auto port = configMgr["RedisServer"]["Port"];
	auto pwd = configMgr["RedisServer"]["Password"];
	_con_pool.reset(new RedisConnectPool(5, host.c_str(), atoi(port.c_str()), pwd.c_str()));
}

RedisMgr::~RedisMgr()
{
	Close();
}

bool RedisMgr::Get(const std::string& key, std::string& value)
{
	auto _connect = _con_pool->getConnection();
	if (_connect == nullptr) {
		std::cout << "Failed to get Redis connection." << std::endl;
		return false;
	}
	auto _reply = (redisReply*)redisCommand(_connect.get(), "GET %s", key.c_str());
	if (_reply->type == REDIS_REPLY_NIL)
	{
		freeReplyObject(_reply);
		return false;
	}

	if (_reply == NULL) 
	{
		printf("Failed to execute command: GET %s\n", key.c_str());
		return false;
	}

	if (_reply->type != REDIS_REPLY_STRING)
	{
		freeReplyObject(_reply);
		printf("Expected string reply for key '%s', but got type %d\n", key.c_str(), _reply->type);
		return false;
	}
	value = _reply->str;
	freeReplyObject(_reply);
	_con_pool->returnConnection(std::move(_connect));
	return true;
}

bool RedisMgr::Set(const std::string& key, const std::string& value) {
	auto _connect = _con_pool->getConnection();
	if (_connect == nullptr) {
		std::cout << "Failed to get Redis connection." << std::endl;
		return false;
	}
	auto _reply = (redisReply*)redisCommand(_connect.get(), "SET %s %s", key.c_str(), value.c_str());

	// 如果返回NULL说明执行失败
	if (_reply == NULL)
	{
		std::cout << "Failed to execute command: SET " << key << " " << value << std::endl;
		freeReplyObject(_reply);
		return false;
	}

	if (!((_reply->type == REDIS_REPLY_STATUS) && (strcmp(_reply->str, "ok") == 0 || strcmp(_reply->str, "OK") == 0)))
	{
		std::cout << "Failed to execute command: SET " << key << " " << value << std::endl;
		freeReplyObject(_reply);
		return false;
	}

	freeReplyObject(_reply);
	std::cout  << "Successfully set key : " << key << " with value : " << value << std::endl;
	_con_pool->returnConnection(std::move(_connect));
	return true;
}

bool RedisMgr::Auth(const std::string& password)
{
	auto _connect = _con_pool->getConnection();
	if (_connect == nullptr) {
		std::cout << "Failed to get Redis connection." << std::endl;
		return false;
	}
	auto _reply = (redisReply*)redisCommand(_connect.get(), "AUTH %s", password.c_str());
	if (_reply == NULL)
	{
		printf("Failed to execute command: AUTH %s\n", password.c_str());
		return false;
	}
	if (_reply->type != REDIS_REPLY_STATUS || strcmp(_reply->str, "OK") != 0)
	{
		printf("Authentication failed: %s\n", _reply->str);
		freeReplyObject(_reply);
		return false;
	}
	freeReplyObject(_reply);
	printf("Authentication successful\n");
	_con_pool->returnConnection(std::move(_connect));
	return true;
}

bool RedisMgr::LPush(const std::string& key, const std::string& value)
{
	auto _connect = _con_pool->getConnection();
	if (_connect == nullptr) {
		std::cout << "Failed to get Redis connection." << std::endl;
		return false;
	}
	auto _reply = (redisReply*)redisCommand(_connect.get(), "LPUSH %s %s", key.c_str(), value.c_str());
	if (NULL == _reply)
	{
		std::cout << "Execut command [ LPUSH " << key << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}
	if (_reply->type != REDIS_REPLY_INTEGER || _reply->integer <= 0) {
		std::cout << "Execut command [ LPUSH " << key << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}
	std::cout << "Execut command [ LPUSH " << key << "  " << value << " ] success ! " << std::endl;
	freeReplyObject(_reply);
	_con_pool->returnConnection(std::move(_connect));
	return true;
}

bool RedisMgr::LPop(const std::string& key, std::string& value) {
	auto _connect = _con_pool->getConnection();
	if (_connect == nullptr) {
		std::cout << "Failed to get Redis connection." << std::endl;
		return false;
	}
	auto _reply = (redisReply*)redisCommand(_connect.get(), "LPOP %s ", key.c_str());
	if (_reply == nullptr || _reply->type == REDIS_REPLY_NIL) {
		std::cout << "Execut command [ LPOP " << key << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}
	value = _reply->str;
	std::cout << "Execut command [ LPOP " << key << " ] success ! " << std::endl;
	freeReplyObject(_reply);
	_con_pool->returnConnection(std::move(_connect));
	return true;
}

bool RedisMgr::RPush(const std::string& key, const std::string& value) {
	auto _connect = _con_pool->getConnection();
	if (_connect == nullptr) {
		std::cout << "Failed to get Redis connection." << std::endl;
		return false;
	}
	auto _reply = (redisReply*)redisCommand(_connect.get(), "RPUSH %s %s", key.c_str(), value.c_str());
	if (NULL == _reply)
	{
		std::cout << "Execut command [ RPUSH " << key << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}
	if (_reply->type != REDIS_REPLY_INTEGER || _reply->integer <= 0) {
		std::cout << "Execut command [ RPUSH " << key << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}
	std::cout << "Execut command [ RPUSH " << key << "  " << value << " ] success ! " << std::endl;
	freeReplyObject(_reply);
	_con_pool->returnConnection(std::move(_connect));
	return true;
}

bool RedisMgr::RPop(const std::string& key, std::string& value) {
	auto _connect = _con_pool->getConnection();
	if (_connect == nullptr) {
		std::cout << "Failed to get Redis connection." << std::endl;
		return false;
	}
	auto _reply = (redisReply*)redisCommand(_connect.get(), "RPOP %s ", key.c_str());
	if (_reply == nullptr || _reply->type == REDIS_REPLY_NIL) {
		std::cout << "Execut command [ RPOP " << key << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}
	value = _reply->str;
	std::cout << "Execut command [ RPOP " << key << " ] success ! " << std::endl;
	freeReplyObject(_reply);
	_con_pool->returnConnection(std::move(_connect));
	return true;
}

bool RedisMgr::HSet(const std::string& key, const std::string& hkey, const std::string& value) {
	auto _connect = _con_pool->getConnection();
	if (_connect == nullptr) {
		std::cout << "Failed to get Redis connection." << std::endl;
		return false;
	}
	auto _reply = (redisReply*)redisCommand(_connect.get(), "HSET %s %s %s", key.c_str(), hkey.c_str(), value.c_str());
	if (_reply == nullptr || _reply->type != REDIS_REPLY_INTEGER) {
		std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}
	std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << value << " ] success ! " << std::endl;
	freeReplyObject(_reply);
	_con_pool->returnConnection(std::move(_connect));
	return true;
}

bool RedisMgr::HSet(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen)
{
	const char* argv[4];
	size_t argvlen[4];
	argv[0] = "HSET";
	argvlen[0] = 4;
	argv[1] = key;
	argvlen[1] = strlen(key);
	argv[2] = hkey;
	argvlen[2] = strlen(hkey);
	argv[3] = hvalue;
	argvlen[3] = hvaluelen;
	auto _connect = _con_pool->getConnection();
	if (_connect == nullptr) {
		std::cout << "Failed to get Redis connection." << std::endl;
		return false;
	}
	auto _reply = (redisReply*)redisCommandArgv(_connect.get(), 4, argv, argvlen);
	if (_reply == nullptr || _reply->type != REDIS_REPLY_INTEGER) {
		std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << hvalue << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}
	std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << hvalue << " ] success ! " << std::endl;
	freeReplyObject(_reply);
	_con_pool->returnConnection(std::move(_connect));
	return true;
}

std::string RedisMgr::HGet(const std::string& key, const std::string& hkey)
{
	const char* argv[3];
	size_t argvlen[3];
	argv[0] = "HGET";
	argvlen[0] = 4;
	argv[1] = key.c_str();
	argvlen[1] = key.length();
	argv[2] = hkey.c_str();
	argvlen[2] = hkey.length();
	auto _connect = _con_pool->getConnection();
	if (_connect == nullptr) {
		std::cout << "Failed to get Redis connection." << std::endl;
		return "";
	}
	auto _reply = (redisReply*)redisCommandArgv(_connect.get(), 3, argv, argvlen);
	if (_reply == nullptr || _reply->type == REDIS_REPLY_NIL) {
		freeReplyObject(_reply);
		std::cout << "Execut command [ HGet " << key << " " << hkey << "  ] failure ! " << std::endl;
		return "";
	}
	std::string value = _reply->str;
	freeReplyObject(_reply);
	std::cout << "Execut command [ HGet " << key << " " << hkey << " ] success ! " << std::endl;
	_con_pool->returnConnection(std::move(_connect));
	return value;
}

bool RedisMgr::Del(const std::string& key)
{
	auto _connect = _con_pool->getConnection();
	if (_connect == nullptr) {
		std::cout << "Failed to get Redis connection." << std::endl;
		return false;
	}
	auto _reply = (redisReply*)redisCommand(_connect.get(), "DEL %s", key.c_str());
	if (_reply == nullptr || _reply->type != REDIS_REPLY_INTEGER) {
		std::cout << "Execut command [ Del " << key << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}
	std::cout << "Execut command [ Del " << key << " ] success ! " << std::endl;
	freeReplyObject(_reply);
	_con_pool->returnConnection(std::move(_connect));
	return true;
}

bool RedisMgr::ExistsKey(const std::string& key)
{
	auto _connect = _con_pool->getConnection();
	if (_connect == nullptr) {
		std::cout << "Failed to get Redis connection." << std::endl;
		return false;
	}
	auto _reply = (redisReply*)redisCommand(_connect.get(), "exists %s", key.c_str());
	if (_reply == nullptr || _reply->type != REDIS_REPLY_INTEGER || _reply->integer == 0) {
		std::cout << "Not Found [ Key " << key << " ]  ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}
	std::cout << " Found [ Key " << key << " ] exists ! " << std::endl;
	freeReplyObject(_reply);
	_con_pool->returnConnection(std::move(_connect));
	return true;
}

void RedisMgr::Close()
{
	_con_pool->Stop();
}

