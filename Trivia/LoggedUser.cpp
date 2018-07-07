#include "LoggedUser.h"

LoggedUser::LoggedUser() : LoggedUser("", Client(0 , nullptr))
{
}

LoggedUser::LoggedUser(const std::string& username, Client& client) : m_username(username), _client(client), _data({false, 0, false, 0})
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

UserRoomData & LoggedUser::getRoomData()
{
	return _data;
}

bool LoggedUser::operator==(const LoggedUser & othr) const
{
	return !m_username.compare(othr.m_username);
}

bool LoggedUser::operator<(const LoggedUser & othr) const
{
	return m_username < othr.m_username	;
}
