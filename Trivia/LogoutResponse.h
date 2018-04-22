#pragma once

class LogoutResponse
{
private:
	unsigned int status;
public:
	LogoutResponse(unsigned int);
	unsigned int getStatus();
};