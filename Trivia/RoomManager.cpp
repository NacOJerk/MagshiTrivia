#include "RoomManager.h"
#include "Room.h"

unsigned int RoomManager::id = 0;
RoomManager::RoomManager(map<unsigned int, Room> rooms) : m_rooms(rooms)
{}

unsigned int RoomManager::generateId()
{
	return ++id;
}

void RoomManager::createRoom(LoggedUser user, unsigned int maxPlayers, unsigned int timePerQuestion)
{
	RoomData data(user.getUsername(), maxPlayers, timePerQuestion, false);
	vector<LoggedUser> vec;
	vec.push_back(user);
	Room room(data, vec);
	m_rooms[generateId()] = room;
}

void RoomManager::deleteRoom(unsigned int id)
{
	m_rooms.erase(id);
}

bool RoomManager::getRoomState(unsigned int id)
{
	return m_rooms[id].getData().getIsActive();
}

vector<Room> RoomManager::getRooms()
{
	vector<Room> vec;
	for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
	{
		vec.push_back(it->second);
	}
	return vec;
}