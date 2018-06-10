#pragma once
#include <string>

class ErrorResponse
{
	std::string _message;
public:
	ErrorResponse(std::string);
	std::string getMessage();
};

