#include "CreateRoomResponse.h"

CreateRoomResponse::CreateRoomResponse(unsigned int _status) : status(_status)
{
}

unsigned int CreateRoomResponse::getStatus()
{
	return status;
}