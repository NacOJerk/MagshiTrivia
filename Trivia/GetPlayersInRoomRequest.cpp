#include "GetPlayersInRoomRequest.h"

GetPlayersInRoomRequest::GetPlayersInRoomRequest(unsigned int _roomId) : roomId(_roomId)
{}

unsigned int GetPlayersInRoomRequest::getRoomId()
{
	return roomId;
}