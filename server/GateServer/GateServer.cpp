﻿#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "CServer.h"
#include "const.h"

int main()
{
	ConfigMgr gCfgMgr;
	std::string gate_prot_str = gCfgMgr["GateServer"]["Port"];
	unsigned short gate_port = atoi(gate_prot_str.c_str());
	try
	{
		unsigned short port = static_cast<unsigned short>(8080);
		net::io_context ioc{ 1 };
		boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
		signals.async_wait([&ioc](const boost::system::error_code& error, int signal_number) {
			if (error) {
				return;
			}

			ioc.stop();
			});

		std::make_shared<CServer>(ioc, port)->Start();
		ioc.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error:" << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}