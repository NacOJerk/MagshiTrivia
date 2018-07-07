#include "LoginResponse.h"

LoginResponse::LoginResponse(unsigned int status) : _status(status)
{}

unsigned int LoginResponse::getStatus()
{
	return _status;
}