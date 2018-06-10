#pragma once

#include "IDatabase.h"
#include "Communicator.h"
#include "RequestHandlerFactory.h"

class Server
{
	IDatabase& m_database;
	Communicator m_communicator;
	RequestHandlerFactory m_handlerFactory;
public:
	void run();
};

