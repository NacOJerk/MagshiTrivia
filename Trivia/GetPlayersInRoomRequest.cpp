#include "GetPlayersInRoomRequest.h"

GetPlayersInRoomRequest::GetPlayersInRoomRequest(unsigned int roomId) : roomId(roomId)
{}

unsigned int GetPlayersInRoomRequest::getRoomId()
{
	return roomId;
}