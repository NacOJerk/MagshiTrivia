#pragma once

class CreateRoomResponse
{
private:
	unsigned int status;
public:
	CreateRoomResponse(unsigned int);
	unsigned int getStatus();
};