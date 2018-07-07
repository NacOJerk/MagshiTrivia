#pragma once

#include <map>
#include <WinSock2.h>
#include <Windows.h>
#include <thread>
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"
#include "Client.h"
#include "PipeManager.h"
#include "RSA.h"

class RequestHandlerFactory;

using RSA::Key;

class Communicator
{
	RequestHandlerFactory& m_handlerFactory;
	SOCKET _serverSocket;
	std::pair<Key, Key> _keys;
public:
	Communicator(RequestHandlerFactory&, std::pair<Key, Key>);
	void start(unsigned int port);
private:
	void bindAndListen(unsigned int port);
	void handleRequests();
	void startEncryption(Client&);
	void startThreadForNewClient(SOCKET);
};

