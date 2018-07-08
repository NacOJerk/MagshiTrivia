#include "Room.h"
#include "GetPlayersInRoomResponse.h"
#include "JsonResponsePacketSerializer.h"

Room::Room() : m_metadata(), m_users()
{
}

Room::Room(RoomData data, vector<std::reference_wrapper<LoggedUser>> users, unsigned int id) : m_metadata(data), m_users(users), _id(id)
{
	for (int i = 0; i < users.size(); i++)
	{
		users[i].get().getRoomData().id = id;
		users[i].get().getRoomData().loggedIn = true;
		users[i].get().getRoomData().isAdmin = i == 0 ? true : false;
	}
}

void Room::addUser(LoggedUser& user)
{
	user.getRoomData().id = _id;
	user.getRoomData().loggedIn = true;
	user.getRoomData().isAdmin = m_users.size() > 0 ? false : true;
	m_users.push_back(user);
	std::vector<std::string> users;
	for (auto user : m_users)
	{
		users.push_back(user.get().getUsername());
	}
	buffer buff = JsonResponsePacketSerializer::getInstance()->serializeResponse(GetPlayersInRoomResponse(users, m_metadata.getMaxPlayers()));
	for (int i = 0; i < m_users.size() - 1; i++)
	{
		m_users[i].get().getClient().getPipeManager().write(buff);
	}
}

unsigned int Room::getID() const
{
	return _id;
}

void Room::removeUser(string username)
{
	auto it = m_users.begin();
	for (it; it != m_users.end(); it++)
	{
		if (it->get().getUsername() == username)
			break;
	}
	if (it != m_users.end())
	{
		it->get().getRoomData().id = -1;
		it->get().getRoomData().loggedIn = false;
		it->get().getRoomData().isAdmin = false;
		m_users.erase(it);
		std::vector<std::string> users;
		for (auto user : m_users)
		{
			users.push_back(user.get().getUsername());
		}
		buffer buff = JsonResponsePacketSerializer::getInstance()->serializeResponse(GetPlayersInRoomResponse(users, m_metadata.getMaxPlayers()));
		for (int i = 0; i < m_users.size(); i++)
		{
			m_users[i].get().getClient().getPipeManager().write(buff);
		}
	}
}

vector<std::reference_wrapper<LoggedUser>>& Room::getAllUsers()
{
	return m_users;
}

RoomData Room::getData()
{
	return m_metadata;
}

bool Room::operator==(const Room& othr) const
{
	return _id == othr._id;
}