#include "ErrorResponse.h"

ErrorResponse::ErrorResponse(std::string error) : _message(error)
{}

std::string ErrorResponse::getMessage()
{
	return _message;
}