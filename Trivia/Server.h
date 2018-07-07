#pragma once

#include "IDatabase.h"
#include "SQLDatabase.h"
#include "Communicator.h"
#include "RequestHandlerFactory.h"
#include "RSA.h"

using RSA::Key;

class Server
{
	SQLDatabase m_database;
	Communicator m_communicator;
	RequestHandlerFactory m_handlerFactory;
public:
	Server(std::pair<Key, Key>);
	void run();
	Communicator& getCommunicator();
};

