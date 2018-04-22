#pragma once
#include <vector>
#include "RoomData.h"

using std::vector;

class GetRoomsResponse
{
private:
	unsigned int status;
	vector<RoomData> rooms;
public:
	GetRoomsResponse(unsigned int, vector<RoomData>);
	unsigned int getStatus();
	vector<RoomData> getRooms();
};