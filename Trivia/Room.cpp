#include "Room.h"

Room::Room() : m_metadata(), m_users()
{
}

Room::Room(RoomData data, vector<LoggedUser> users) : m_metadata(data), m_users(users)
{}

void Room::addUser(LoggedUser user)
{
	m_users.push_back(user);
}

void Room::removeUser(string username)
{
	auto it = m_users.begin();
	for (it; it != m_users.end(); it++)
	{
		if (it->getUsername() == username)
			break;
	}
	if (it != m_users.end())
		m_users.erase(it);
}

vector<LoggedUser> Room::getAllUsers()
{
	return m_users;
}

RoomData Room::getData()
{
	return m_metadata;
}