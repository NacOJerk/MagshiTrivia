#pragma once

#include "IDatabase.h"
#include "SQLDatabase.h"
#include "Communicator.h"
#include "RequestHandlerFactory.h"

class Server
{
	SQLDatabase m_database;
	Communicator m_communicator;
	RequestHandlerFactory m_handlerFactory;
public:
	Server();
	void run();
};

