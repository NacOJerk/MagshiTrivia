#include "GetRoomsResponse.h"

GetRoomsResponse::GetRoomsResponse(unsigned int status, vector<Room> rooms) : status(status), rooms(rooms)
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