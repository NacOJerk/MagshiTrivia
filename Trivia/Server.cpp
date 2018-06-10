#include "Server.h"
#include <thread>
#include <iostream>
#include <string>

Server* Server::_instance = nullptr;

Server::Server() : m_handlerFactory(m_database), m_communicator(m_handlerFactory)
{
}

Server* Server::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Server();
	}
	return _instance;
}

Communicator& Server::getCommunicator()
{
	return m_communicator;
}

void Server::run()
{
	m_database.open("GOD.DB");
	m_communicator.start(12345);
	while (true)
	{
		std::string str;
		std::cin >> str;
		if (str == "EXIT")
			break;
	}
}
