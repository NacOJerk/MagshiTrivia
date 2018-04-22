#pragma once

class JoinRoomResponse
{
private:
	unsigned int status;
public:
	JoinRoomResponse(unsigned int);
	unsigned int getStatus();
};