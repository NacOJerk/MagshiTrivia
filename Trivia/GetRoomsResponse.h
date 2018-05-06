#pragma once
#include <vector>
#include "Room.h"

using std::vector;

class GetRoomsResponse
{
private:
	unsigned int status;
	vector<Room> rooms;
public:
	GetRoomsResponse(unsigned int, vector<Room>);
	unsigned int getStatus();
	vector<Room> getRooms();
};