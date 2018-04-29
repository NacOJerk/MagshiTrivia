#include "Server.h"

Server::Server() : m_handlerFactory(m_database), m_communicator(m_handlerFactory)
{
}

void Server::run()
{
	m_communicator.bindAndListen(12345);
	m_communicator.handleRequests();
}
