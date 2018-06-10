#include "Request.h"

Request::Request(RequestId id, std::time_t receivalTime, buffer buffer) : _id(id), _receivalTime(receivalTime), _buffer(buffer)
{
}

RequestId Request::getID()
{
	return _id;
}

std::time_t Request::getRecivalTime()
{
	return _receivalTime;
}

buffer Request::getBuffer()
{
	return _buffer;
}
