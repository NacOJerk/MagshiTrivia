#pragma once

#include <map>
#include <WinSock2.h>
#include <Windows.h>
#include <thread>
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"
#include "Client.h"
#include "PipeManager.h"

class RequestHandlerFactory;

class Communicator
{
	RequestHandlerFactory& m_handlerFactory;
	SOCKET _serverSocket;
public:
	Communicator(RequestHandlerFactory&);
	void start(unsigned int port);
private:
	void bindAndListen(unsigned int port);
	void handleRequests();
	
	void startThreadForNewClient(SOCKET);
};

