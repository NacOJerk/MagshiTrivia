#pragma once

#include <map>
#include "Room.h"
#include "LoggedUser.h"

using std::map;

class RoomManager
{
private:
	static unsigned int id;
	map<unsigned int, Room> m_rooms;
public:
	RoomManager(map<unsigned int, Room>);
	void createRoom(LoggedUser, unsigned int, unsigned int);
	void deleteRoom(unsigned int);
	bool getRoomState(unsigned int);
	vector<Room> getRooms();
	static unsigned int generateId();
};