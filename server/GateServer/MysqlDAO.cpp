#include "MysqlDAO.h"

MysqlDAO::MysqlDAO()
{
	auto& cfg = ConfigMgr::GetInstance();
	const auto& host = cfg["MysqlServer"]["Host"];
	const auto& port = cfg["MysqlServer"]["Port"];
	const auto& user = cfg["MysqlServer"]["User"];
	const auto& password = cfg["MysqlServer"]["Password"];
	const auto& schema = cfg["MysqlServer"]["Schema"];

	_pool.reset(new MysqlPool(
		host + ":" + port,
		user,
		password,
		schema,
		5
	));
}

int MysqlDAO::RegUser(const std::string& name, const std::string& email, const std::string& pwd)
{
	auto connection = _pool->getConnection();
	Defer defer([this, &connection]() {
		if (connection) {
			_pool->returnConnection(std::move(connection));
		}
		});
	if (connection == nullptr) {
		std::cout << "MysqlDAO::RegUser: Failed to get connection from pool." << std::endl;
		return 0;
	}

	try
	{
		//调用储存过程注册用户
		std::unique_ptr<sql::PreparedStatement> pstmt(connection->getConnection().prepareStatement("CALL reg_user(?,?,?,@result)"));

		pstmt->setString(1, name);
		pstmt->setString(2, email);
		pstmt->setString(3, pwd);

		std::cout << "MysqlDAO::RegUser: Registering user: " << name << ", email: " << email << std::endl;
		pstmt->execute();

		std::cout << "Here" << std::endl;

		//查询输出参数
		std::unique_ptr<sql::Statement> stmt(connection->getConnection().createStatement());
		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT @result AS result"));
		if (res->next()) {
			int result = res->getInt("result");
			std::cout << "Result: " << result << std::endl;
			return result;
		}

		std::cout << "MysqlDAO::RegUser: Failed to get result from stored procedure." << std::endl;
		return -1;
	}
	catch (const sql::SQLException& err)
	{
		std::cerr << "DAO: SQLException: " << err.what();
		std::cerr << " (MySQL error code: " << err.getErrorCode();
		std::cerr << ", SQLState: " << err.getSQLState() << ")" << std::endl;
		return -1;
	}
}

int MysqlDAO::CheckUser(const std::string& name, const std::string& password, UserInfo& userInfo)
{
	auto connection = _pool->getConnection();
	Defer defer([this, &connection]() {
		if (connection) {
			_pool->returnConnection(std::move(connection));
		}
		});
	if (connection == nullptr) {
		std::cout << "MysqlDAO::CheckUser: Failed to get connection from pool." << std::endl;
		return 0;
	}
	try
	{
		if (!connection) {
			return 0;
	}
		std::unique_ptr<sql::PreparedStatement> pstmt(connection->getConnection().prepareStatement("SELECT * FROM user WHERE name = ? "));
		pstmt->setString(1, name);
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

		// 检查结果集是否有数据
		if (!res->next()) {
			std::cout << "MysqlDAO::CheckUser: User not found." << std::endl;
			return -1; // 用户不存在
		}

		res->beforeFirst();

		std::string origin_pwd = "";
		// 遍历结果集
		while (res->next()) {
			origin_pwd = res->getString("password");
			// 输出查询到的密码
			std::cout << "Password: " << origin_pwd << std::endl;
			break;
		}
		std::cout << password << " | " << origin_pwd << std::endl;

		if (password != origin_pwd) {
			return -2;
		}

		userInfo.name = name;
		userInfo.email = res->getString("email");
		userInfo.uid = res->getInt("uid");
		userInfo.password = origin_pwd;
		return std::atoi(userInfo.uid.c_str());
	}
	catch (const sql::SQLException& err)
	{
		std::cerr << "DAO: SQLException: " << err.what();
		std::cerr << " (MySQL error code: " << err.getErrorCode();
		std::cerr << ", SQLState: " << err.getSQLState() << ")" << std::endl;
		return 0;
	}
}