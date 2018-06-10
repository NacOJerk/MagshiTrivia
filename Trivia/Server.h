#pragma once

#include "IDatabase.h"
#include "SQLDatabase.h"
#include "Communicator.h"
#include "RequestHandlerFactory.h"

class Server
{
	static Server* _instance;
	SQLDatabase m_database;
	Communicator m_communicator;
	RequestHandlerFactory m_handlerFactory;
	Server();
public:
	static Server* getInstance();
	void run();
	Communicator& getCommunicator();
};

