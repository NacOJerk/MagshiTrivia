#pragma once

#include <WinSock2.h>
#include <thread>
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"

class Communicator
{
	RequestHandlerFactory& m_handlerFactory;
	SOCKET _serverSocket;
public:
	Communicator(RequestHandlerFactory&);
	void bindAndListen(unsigned int port);
	void handleRequests();
private:
	byte* readBytes(SOCKET, unsigned int);
	void sendDataToSocket(SOCKET, char*, unsigned int);
	byte getId(SOCKET);
	unsigned int getLength(SOCKET);
	buffer getBuffer(SOCKET, unsigned int);
	void sendBuffer(SOCKET, buffer);
	void startThreadForNewClient(SOCKET);
};

