#include "JoinRoomResponse.h"

JoinRoomResponse::JoinRoomResponse(unsigned int status) : status(status)
{
}

unsigned int JoinRoomResponse::getStatus()
{
	return status;
}