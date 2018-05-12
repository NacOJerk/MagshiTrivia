#pragma once

#include <WinSock2.h>
#include "../locked.hpp"
#include "IRequestHandler.h"
#include "LoggedUser.h"

class LoggedUser;
class IRequestHandler;

class Client
{
	SOCKET _socket;
	locked<IRequestHandler*> _handler;
	LoggedUser* _usr;
public:
	Client(SOCKET, IRequestHandler*);
	~Client();
	SOCKET getSocket();
	locked<IRequestHandler*>& getHandler();
	void setUser(LoggedUser*);
	bool isLoggedIn() const;
	LoggedUser& getUser();//User only after a check isLoggedIn()
};
