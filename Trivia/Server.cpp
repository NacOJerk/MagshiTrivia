#include "Server.h"
#include <thread>
#include <iostream>
#include <string>


Server::Server(std::pair<Key, Key> keys) : m_handlerFactory(m_database), m_communicator(m_handlerFactory, keys)
{
}

Communicator& Server::getCommunicator()
{
	return m_communicator;
}

void Server::run()
{
	m_database.open("TriviaData.DB");
	m_communicator.start(12345);
	while (true)
	{
		std::string str;
		std::cin >> str;
		if (str == "EXIT")
			break;
	}
}
