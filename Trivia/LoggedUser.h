#pragma once
#include <WinSock2.h>
#include <string>
#include "Client.h"

class Client;

class LoggedUser
{
	std::string m_username;
	Client& _client;
public:
	LoggedUser();
	LoggedUser(const std::string&, Client&);
	std::string getUsername() const;
	Client& getClient();
	LoggedUser& operator=(LoggedUser&);
};

