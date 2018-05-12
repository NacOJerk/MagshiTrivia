#include "JoinRoomResponse.h"

JoinRoomResponse::JoinRoomResponse(unsigned int _status) : status(_status)
{
}

unsigned int JoinRoomResponse::getStatus()
{
	return status;
}