#pragma once

class LeaveRoomResponse
{
private:
	unsigned int status;
public:
	LeaveRoomResponse(const unsigned int status);
	unsigned int getStatus() const;
};