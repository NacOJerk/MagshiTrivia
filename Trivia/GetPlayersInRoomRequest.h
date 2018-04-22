#pragma once

class GetPlayersInRoomRequest
{
private:
	unsigned int roomId;
public:
	GetPlayersInRoomRequest(unsigned int);
	unsigned int getRoomId();
};