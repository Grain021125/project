#pragma once

#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include "Singleton.h"
#include <functional>
#include <map>
#include <unordered_map>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "ConfigMgr.h"
#include <atomic>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <hiredis.h>
#include <stdio.h>

#define USERTOKENPREFIX  "utoken_"

#define MAX_ID_LENGTH  1024
#define MAX_DATA_LENGTH  1024 * 64 // 64KB for data length

#define HEAD_TOTAL_LEN 4
#define HEAD_ID_LEN 2
#define HEAD_DATA_LEN 2

#define MAX_SENDQUE_SIZE 1000 // Maximum size of the send queue

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

enum ErrorCodes {
	SUCCESS = 0,
	ERROR_JSON = 1001,
	RPC_FAILD = 1002,
	VARIFYCODE_EXPIRED = 1003,
	USER_EXIST = 1004,
	MYSQL_FAILD = 1005,
	USER_NOT_EXIST = 1006,
	PASSWORD_WRONG = 1007,
	UID_INVALID = 1008,
	TOKEN_INVALID = 1009,
};

enum MsgIds{
	MSG_CHAT_LOGIN = 1005,
	MSG_CHAT_LOGIN_RSP = 1006,
	// Add other message IDs as needed
};

class Defer {
public:
	Defer(std::function<void()> func) : _func(std::move(func)) {}
	~Defer() {
		if (_func) {
			_func();
		}
	}
private:
	std::function<void()> _func;
};