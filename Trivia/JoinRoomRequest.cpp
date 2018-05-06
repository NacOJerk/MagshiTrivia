#include "JoinRoomRequest.h"

JoinRoomRequest::JoinRoomRequest(unsigned int roomId) : roomId(roomId)
{}

unsigned int JoinRoomRequest::getRoomId()
{
	return roomId;
}