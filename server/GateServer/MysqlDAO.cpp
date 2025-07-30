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
			_pool->returnConnection(std::move(connection));
			return result;
		}

		std::cout << "MysqlDAO::RegUser: Failed to get result from stored procedure." << std::endl;
		_pool->returnConnection(std::move(connection));
		return -1;
	}
	catch (const sql::SQLException& err)
	{
		if (connection){
			_pool->returnConnection(std::move(connection));
		}
		std::cerr << "DAO: SQLException: " << err.what();
		std::cerr << " (MySQL error code: " << err.getErrorCode();
		std::cerr << ", SQLState: " << err.getSQLState() << ")" << std::endl;
		return -1;
	}
}
