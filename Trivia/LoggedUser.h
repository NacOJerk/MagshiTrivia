#pragma once
#include <WinSock2.h>
#include <string>

class LoggedUser
{
	std::string m_username;
	SOCKET _socket;
public:
	LoggedUser(const std::string&, SOCKET);
	std::string getUsername() const;
	SOCKET getSocket();
};

