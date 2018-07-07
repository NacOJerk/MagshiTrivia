#include "SignupResponse.h"

SignupResponse::SignupResponse(unsigned int status) : _status(status)
{}

unsigned int SignupResponse::getStatus()
{
	return _status;
}