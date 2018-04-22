#pragma once

class JoinRoomRequest
{
private:
	unsigned int roomId;
public:
	JoinRoomRequest(unsigned int);
	unsigned int getRoomId();
};