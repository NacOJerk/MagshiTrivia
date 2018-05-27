#pragma once

class StartGameResponse
{
private:
	unsigned int status;
public:
	StartGameResponse(const unsigned int);
	unsigned int getStatus() const;
};