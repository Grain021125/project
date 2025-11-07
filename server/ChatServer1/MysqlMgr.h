#pragma once
#include "const.h"
#include "MysqlDAO.h"
class MysqlMgr : public Singleton<MysqlMgr>
{
	friend class Singleton<MysqlMgr>;

public:
		MysqlMgr() = default;
		~MysqlMgr() = default;
		int RegUser(const std::string& name, const std::string& email, const std::string& pwd) {
			return _dao.RegUser(name, email, pwd);
		}
		
		int CheckUser(const std::string& name, const std::string& password, UserInfo& userInfo) {
			return _dao.CheckUser(name, password, userInfo);
		}

		UserInfo GetUser(int uid) {
			return _dao.GetUser(uid);
		}

		
private:
	MysqlDAO _dao;
};

