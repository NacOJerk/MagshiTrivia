#include "LogoutResponse.h"

LogoutResponse::LogoutResponse(unsigned int status) : status(status)
{
}

unsigned int LogoutResponse::getStatus()
{
	return status;
}