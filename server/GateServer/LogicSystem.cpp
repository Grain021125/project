#include "LogicSystem.h"
#include "HttpConnection.h"
#include "VarifyGrpcClient.h"
#include "RedisMgr.h"
#include "MysqlMgr.h"

bool LogicSystem::HandleGet(std::string path, std::shared_ptr<HttpConnection> connection)
{
	if (_get_handlers.find(path) == _get_handlers.end()) {
		return false;
	}

	_get_handlers[path](connection);
	return true;
}

bool LogicSystem::HandlePost(std::string path, std::shared_ptr<HttpConnection> connection)
{
	if (_post_handlers.find(path) == _post_handlers.end()) {
		return false;
	}

	_post_handlers[path](connection);
	return true;
}

void LogicSystem::RegGet(std::string url, HttpHandler handler)
{
	_get_handlers.insert(make_pair(url, handler));
}

void LogicSystem::RegPost(std::string url, HttpHandler handler)
{
	_post_handlers.insert(make_pair(url, handler));
}

LogicSystem::LogicSystem() {
	RegGet("/get_test", [](std::shared_ptr<HttpConnection> connection) {
		beast::ostream(connection->_response.body()) << "receive get_test req\n";
		int i = 0;
		for (auto& elem : connection->_get_params) {
			i++;
			beast::ostream(connection->_response.body()) << "param " << i << " key is " << elem.first << "\n";
			beast::ostream(connection->_response.body()) << "param " << i << " key is " << elem.second << "\n";
		}
	});

	RegPost("/get_varifycode", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
		std::cout << "receve body is " << body_str << std::endl;
		connection->_response.set(http::field::content_type, "text/json");
		Json::Value root; //返回的json
		Json::Reader reader;
		Json::Value src_root; //接受的json
		bool parse_success = reader.parse(body_str, src_root);
		if (!parse_success) {
			std::cout << "email: Failed to parse JSON data!" << std::endl;
			root["error"] = ErrorCodes::ERROR_JSON;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		if (!src_root.isMember("email")) {
			std::cout << "email: Failed to parse JSON data!" << std::endl;
			root["error"] = ErrorCodes::ERROR_JSON;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}
		

		auto email = src_root["email"].asString();
		GetVarifyRsp rsp =  VarifyGrpcClient::GetInstance()->GetVarifyCode(email);

		if (rsp.error() == ErrorCodes::RPC_FAILD) {
			std::cout << "Failed to connect VarifyServer" << std::endl;
			root["error"] = ErrorCodes::RPC_FAILD;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		std::cout << "email is " << email << std::endl;
		root["error"] = rsp.error();
		root["email"] = email;
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;
	});

	RegPost("/user_register", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
		std::cout << "receve body is " << body_str << std::endl;
		connection->_response.set(http::field::content_type, "text/json");
		Json::Value root; //返回的json
		Json::Reader reader; //json解析器
		Json::Value src_root; //接受的json
		bool parse_success = reader.parse(body_str, src_root);
		if (!parse_success) {
			std::cout << "user_register: Failed to parse JSON data!" << std::endl;
			root["error"] = ErrorCodes::ERROR_JSON;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		auto email = src_root["email"].asString();
		auto name = src_root["user"].asString();
		auto pwd = src_root["password"].asString();
		auto confirm = src_root["confirm"].asString();

		std::string varify_code;
		bool b_get_varify = RedisMgr::GetInstance()->Get("code_" + src_root["email"].asString(), varify_code);
		// 判断验证码是否失效
		if (!b_get_varify) {
			std::cout << "user_register: Varifycode expired!" << std::endl;
			root["error"] = ErrorCodes::VARIFYCODE_EXPIRED;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		// 检查验证码是否匹配
		if (varify_code != src_root["varifycode"].asString()) {
			std::cout << "user_register: Varifycode is not match!" << std::endl;
			root["error"] = ErrorCodes::VARIFYCODE_EXPIRED;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		//首先访问Redis检查用户是否存在
		//bool b_user_exists = RedisMgr::GetInstance()->ExistsKey("user_" + src_root["user"].asString());
		//if (b_user_exists) {
		//	std::cout << "user_register: User already exists!" << std::endl;
		//	root["error"] = ErrorCodes::USER_EXIST;
		//	std::string jsonstr = root.toStyledString();
		//	beast::ostream(connection->_response.body()) << jsonstr;
		//	return true;
		//}

		//TODO: 访问MySQL检查用户是否存在
		int uid = MysqlMgr::GetInstance()->RegUser(
			name,
			email,
			pwd
		);
		if (uid == 0) {
			std::cout << "user_register: User or email already exists!" << std::endl;
			root["error"] = ErrorCodes::USER_EXIST;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}
		if (uid == -1) {
			std::cout << "user_register: MySQL connection error!" << std::endl;
			root["error"] = ErrorCodes::MYSQL_FAILD;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		root["error"] = ErrorCodes::SUCCESS;
		root["uid"] = uid;
		root["user"] = src_root["user"].asString();
		root["email"] = src_root["email"].asString();
		root["password"] = src_root["password"].asString();
		root["varifycode"] = src_root["varifycode"].asString();
		root["confirm"] = src_root["confirm"].asString();
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;
		});

	RegPost("/user_login", [](std::shared_ptr<HttpConnection> connection) {
		auto body = boost::beast::buffers_to_string(connection->_request.body().data());
		std::cout << "received body is " << body << std::endl;
		connection->_response.set(http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;
		Json::Value src_root;
		bool parse_success = reader.parse(body, src_root);
		if (!parse_success) {
			std::cout << "user_login: Failed to parse JSON data!" << std::endl;
			root["error"] = ErrorCodes::ERROR_JSON;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		auto name = src_root["user"].asString();
		auto pwd = src_root["password"].asString();

		UserInfo userInfo;
		int login_result = MysqlMgr::GetInstance()->CheckUser(name, pwd, userInfo);
		if (login_result == -1) {
			std::cout << "user_login: User doesn\'t exists." << std::endl;
			root["error"] = ErrorCodes::USER_NOT_EXIST;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		if (login_result == -2) {
			std::cout << "user_login: Password is wrong!" << std::endl;
			root["error"] = ErrorCodes::PASSWORD_WRONG;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}
		
		//TODO: 登录成功,查询StatusServer找到合适的连接	

		std::cout << "user_login: Login success!" << std::endl;
		root["error"] = ErrorCodes::SUCCESS;
		root["user"] = name;
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;
		});
}

