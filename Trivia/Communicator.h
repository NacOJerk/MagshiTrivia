#pragma once

#include <map>
#include <WinSock2.h>
#include <Windows.h>
#include <thread>
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"
#include "Client.h"

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
	byte* readBytes(SOCKET, unsigned int);
	void sendDataToSocket(SOCKET, char*, unsigned int);
	byte getId(SOCKET);
	unsigned int getLength(SOCKET);
	buffer getBuffer(SOCKET, unsigned int);
	void sendBuffer(SOCKET, buffer);
	void startThreadForNewClient(SOCKET);
};

