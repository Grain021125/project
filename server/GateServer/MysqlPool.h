#pragma once
#include "const.h"
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/exception.h>

/*
* 心跳检测功能防止连接超时
*/
class SqlConnection {
public:
	SqlConnection(sql::Connection* con, int64_t lasttime): _connection(con), _last_op_time(lasttime) {}

	sql::Connection& getConnection() const {
		return *_connection;
	}
	int64_t getLastOpTime() const {
		return _last_op_time;
	}
	
	void setConnection(sql::Connection* newcon) {
		_connection.reset(newcon);
	}

	void setLastOpTime(long long time) {
		_last_op_time = time;
	}
private:
	std::unique_ptr<sql::Connection> _connection;
	int64_t _last_op_time;
};

class MysqlPool
{
public:
	MysqlPool(const std::string& url, const std::string& user, const std::string& password, const std::string& schema, int poolsize);

	~MysqlPool();

	void Stop();

	void checkConnection();
	std::unique_ptr<SqlConnection> getConnection();
	void returnConnection(std::unique_ptr<SqlConnection> connection);


private:
	std::string _url;
	std::string _user;
	std::string _password;
	std::string _schema;
	int _poolsize;
	std::queue<std::unique_ptr<SqlConnection>> _pool;
	std::mutex _mutex;
	std::condition_variable _cond_var;
	std::atomic<bool> _b_stop;
	std::thread _check_thread;
};

