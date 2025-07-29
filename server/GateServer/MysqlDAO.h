#pragma once
#include "const.h"
#include "MysqlPool.h"

struct UserInfo
{
	std::string name;
	std::string password;
	std::string uid;
	std::string email;
};

class MysqlDAO
{
public:
	MysqlDAO();
	~MysqlDAO() = default;
	int RegUser(const std::string& name, const std::string& email, const std::string& pwd);
private:
	std::unique_ptr<MysqlPool> _pool;
};

