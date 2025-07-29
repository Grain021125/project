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
#include "ConfigMgr.h"
#include <atomic>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <hiredis.h>
#include <stdio.h>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

enum ErrorCodes {
	SUCCESS = 0,
	ERROR_JSON = 1001,
	RPC_FAILD = 1002,
	VARIFYCODE_EXPIRED = 1003,
	USER_EXIST = 1004
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