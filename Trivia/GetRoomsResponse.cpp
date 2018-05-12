#include "GetRoomsResponse.h"

GetRoomsResponse::GetRoomsResponse(unsigned int _status, vector<Room> _rooms) : status(_status), rooms(_rooms)
{
}

vector<Room> GetRoomsResponse::getRooms()
{
	return rooms;
}

unsigned int GetRoomsResponse::getStatus()
{
	return status;
}