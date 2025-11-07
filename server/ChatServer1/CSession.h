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
class LogicNode;

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
	std::string GetUserId();

	void AsyncReadHead(int);
	void AsyncReadBody(int);

	void AsyncSend(const char*, uint16_t, uint16_t);
	void HandleSend(const boost::system::error_code&, std::shared_ptr<CSession>);
	

	void Close();
private:
	tcp::socket _socket;
	CServer* _server;
	bool _b_close;
	bool _b_head_parse;
	std::string _session_id;

	std::shared_ptr<MsgNode> _recv_head_node;
	std::shared_ptr<RecvNode> _recv_msg_node;

	std::array<char, HEAD_TOTAL_LEN> _head_buffer;
	std::array<char, MAX_DATA_LENGTH> _body_buffer; // At most 64KB buffer for body

	std::deque<std::shared_ptr<SendNode>> _send_queue; // Queue for outgoing messages

	std::mutex _mutex; // Protects the session state
	std::mutex _send_mutex; // Protects the send operation
};

class LogicNode {
	public:
	LogicNode(std::shared_ptr<CSession> session, std::shared_ptr<RecvNode> msg_node)
		: _session(session), _msg_node(msg_node) {}

	std::shared_ptr<CSession> _session;
	std::shared_ptr<RecvNode> _msg_node;
};

