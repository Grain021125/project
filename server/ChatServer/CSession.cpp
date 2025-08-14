#include "CSession.h"
#include "CServer.h"
#include <boost/uuid.hpp>

CSession::CSession(boost::asio::io_context& io_context, CServer* server)
	: _socket(io_context), _server(server), _session_id(boost::uuids::to_string(boost::uuids::random_generator()()))
{
	std::cout << "New session created with ID: " << _session_id << std::endl;
}

tcp::socket& CSession::GetSocket()
{
	return _socket;
}

void CSession::Start()
{
	AsyncReadHead(HEAD_TOTAL_LEN);
}

void CSession::Close() {
	std::lock_guard<std::mutex> lock(_mutex);
	if (_b_close) {
		return; // 如果已经关闭，则直接返回
	}
	_b_close = true; // 设置为已关闭状态
	std::cout << "Closing session with ID: " << _session_id << std::endl;
	_socket.close(); // 关闭socket连接
	if (_server) {
		_server->ClearSessions(_session_id); // 通知服务器清除该会话
	}
}

std::string CSession::GetSessionID()
{
	return _session_id;
}

void CSession::AsyncReadHead(int total_len)
{
	auto self = shared_from_this();
	memset(_head_buffer, 0, HEAD_TOTAL_LEN);
	boost::asio::async_read(_socket, boost::asio::buffer(_head_buffer, HEAD_TOTAL_LEN), [self, this](const boost::system::error_code& ec, std::size_t bytesTranfered) {
		if (ec) {
			std::cout << "Error reading header: " << ec.message() << std::endl;
			Close();
			return;
		}

		if (bytesTranfered != HEAD_TOTAL_LEN) {
			std::cout << "Error: Incomplete header received, expected " << HEAD_TOTAL_LEN << " bytes, got " << bytesTranfered << " bytes." << std::endl;
			Close();
			return;
		}


		//TODO: 解析头部数据

		});
}

void CSession::AsyncReadBody(int)
{
}
