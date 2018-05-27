#pragma once
#include "consts.hpp"

class CloseRoomResponse
{
private:
	unsigned int status;
public:
	CloseRoomResponse(const unsigned int);
	unsigned int getStatus() const;
};