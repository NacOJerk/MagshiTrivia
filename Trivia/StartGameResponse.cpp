#include "StartGameResponse.h"

StartGameResponse::StartGameResponse(const unsigned int _status) : status(_status)
{}

unsigned int StartGameResponse::getStatus() const
{
	return status;
}