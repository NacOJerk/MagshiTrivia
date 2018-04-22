#pragma once

#include <map>
#include "Room.h"
#include "LoggedUser.h"

using std::map;

class RoomManager
{
private:
	map<unsigned int, Room> m_rooms;
public:
	RoomManager(map<unsigned int, Room>);
	void createRoom(LoggedUser);
	void deleteRoom(unsigned int);
	bool getRoomState(unsigned int);
	vector<RoomData> getRooms();
};