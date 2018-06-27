#pragma once
class SendAnswerResponse
{
	unsigned int _status;
public:
	SendAnswerResponse(unsigned int status);
	unsigned int getStatus() const;
};

