#include "LogoutResponse.h"

LogoutResponse::LogoutResponse(unsigned int _status) : status(_status)
{
}

unsigned int LogoutResponse::getStatus()
{
	return status;
}