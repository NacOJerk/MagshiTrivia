#pragma once
#include "consts.h"
#include <ctime>

class Request
{
	RequestId _id;
	std::time_t _receivalTime;
	buffer _buffer;
public:
	Request(RequestId, std::time_t, buffer);
	RequestId getID();
	std::time_t getRecivalTime();
	buffer getBuffer();
};

