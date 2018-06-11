#pragma once
#include <WinSock2.h>
#include <string>
#include "Client.h"
#include "UserRoomData.h"

class Client;

class LoggedUser
{
	std::string m_username;
	Client& _client;
	UserRoomData _data;
public:
	LoggedUser();
	LoggedUser(const std::string&, Client&);
	std::string getUsername() const;
	Client& getClient();
	LoggedUser& operator=(LoggedUser&);
	UserRoomData& getRoomData();
	bool operator==(const LoggedUser&) const;
	bool operator<(const LoggedUser&) const;
};

