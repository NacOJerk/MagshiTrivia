#include "RoomManager.h"
#include "Room.h"

unsigned int RoomManager::id = 0;
RoomManager::RoomManager()
{}

bool RoomManager::hasRoom(unsigned int id)
{
	return m_rooms.find(id) != m_rooms.end();
}

unsigned int RoomManager::generateId()
{
	return ++id;
}

void RoomManager::createRoom(LoggedUser& user, unsigned int maxPlayers, unsigned int timePerQuestion, unsigned int amountQuestions)
{
	RoomData data(user.getUsername(), maxPlayers, timePerQuestion, amountQuestions, false);
	vector<std::reference_wrapper<LoggedUser>> vec;
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

vector<Room>& RoomManager::getRooms()
{
	vector<Room> vec;
	for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
	{
		vec.push_back(it->second);
	}
	return vec;
}

Room& RoomManager::getRoom(unsigned int id)
{
	return m_rooms[id];
}