#pragma once
#include <cstdint>
#include "const.h"
#include <iostream>
#include <boost/asio.hpp>

class LogicSystem; // 前向声明

class MsgNode
{
public:
	MsgNode(std::uint16_t max_len)
		: _total_len(max_len), _cur_len(0) {
		_data = new char[max_len + 1];
		_data[max_len] = '\0'; // 确保字符串以null结尾
	}

	~MsgNode()
	{
		delete[] _data;
		_data = nullptr;
		_cur_len = 0;
	}

	void Clear() {
		memset(_data, 0, _total_len);
	}

	uint16_t _total_len;
	uint16_t _cur_len;
	char* _data;
};

class RecvNode :public MsgNode {
	friend class LogicSystem;
public:
	RecvNode(std::uint16_t max_len, std::uint16_t msg_id);

	uint16_t _msg_id;
};

class SendNode :public MsgNode {
	friend class LogicSystem;
public:
	SendNode(const char* msg, std::uint16_t max_len, std::uint16_t msg_id);

	uint16_t _msg_id;
};

