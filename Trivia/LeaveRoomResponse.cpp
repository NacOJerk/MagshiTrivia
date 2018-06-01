#include "LeaveRoomResponse.h"

LeaveRoomResponse::LeaveRoomResponse(unsigned int _status) : status(_status)
{}

unsigned int LeaveRoomResponse::getStatus() const
{
	return status;
}