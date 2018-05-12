#include "JoinRoomRequest.h"

JoinRoomRequest::JoinRoomRequest(unsigned int _roomId) : roomId(_roomId)
{}

unsigned int JoinRoomRequest::getRoomId()
{
	return roomId;
}