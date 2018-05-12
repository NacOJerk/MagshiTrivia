#include "LoggedUser.h"

LoggedUser::LoggedUser(const std::string& username, SOCKET sock) : m_username(username), _socket(sock)
{
}

std::string LoggedUser::getUsername() const
{
	return m_username;
}

SOCKET LoggedUser::getSocket()
{
	return _socket;
}
