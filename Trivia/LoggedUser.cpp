#include "LoggedUser.h"

LoggedUser::LoggedUser() : LoggedUser("", Client(0 , nullptr))
{
}

LoggedUser::LoggedUser(const std::string& username, Client& client) : m_username(username), _client(client)
{
}

std::string LoggedUser::getUsername() const
{
	return m_username;
}

Client& LoggedUser::getClient()
{
	return _client;
}

LoggedUser & LoggedUser::operator=(LoggedUser & usr)
{
	m_username = usr.getUsername();
	_client = usr.getClient();
	return *this;
}
