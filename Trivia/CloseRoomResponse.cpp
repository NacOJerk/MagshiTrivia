#include "CloseRoomResponse.h"

CloseRoomResponse::CloseRoomResponse(const unsigned int _status) : status(_status)
{}

unsigned int CloseRoomResponse::getStatus() const
{
	return status;
}