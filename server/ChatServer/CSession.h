#pragma once
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include "const.h"
#include "MsgNode.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class CServer;

class CSession: public std::enable_shared_from_this<CSession>
{
public:
	CSession(boost::asio::io_context& io_context, CServer* server);
	~CSession() {
		std::cout << "Session with ID: " << _session_id << " is being destroyed." << std::endl;
	}
	tcp::socket& GetSocket();
	void Start();
	std::string GetSessionID();

	void AsyncReadHead(int);
	void AsyncReadBody(int);

	void Close();
private:
	tcp::socket _socket;
	CServer* _server;
	bool _b_close;
	bool _b_head_parse;
	std::string _session_id;
	std::shared_ptr<MsgNode> _recv_head_node;
	char _head_buffer[HEAD_TOTAL_LEN];
	char _body_buffer[1024 * 64]; // 1MB buffer for body
	std::mutex _mutex; // Protects the session state

};

