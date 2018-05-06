#include "CreateRoomResponse.h"

CreateRoomResponse::CreateRoomResponse(unsigned int status) : status(status)
{
}

unsigned int CreateRoomResponse::getStatus()
{
	return status;
}