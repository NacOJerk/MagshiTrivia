#pragma once

#include <map>
#include "Room.h"
#include "LoggedUser.h"

class Room;

class RoomManager
{
private:
	static unsigned int id;
	std::map<unsigned int, Room> m_rooms;
public:
	RoomManager();
	bool hasRoom(unsigned int id);
	Room& getRoom(unsigned int id);
	unsigned int createRoom(LoggedUser&, unsigned int, unsigned int, unsigned int);
	void deleteRoom(unsigned int);
	bool getRoomState(unsigned int);
	vector<Room>& getRooms();
	static unsigned int generateId();
};