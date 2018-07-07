#include "SendAnswerResponse.h"

SendAnswerResponse::SendAnswerResponse(unsigned int status) : _status(status)
{
}

unsigned int SendAnswerResponse::getStatus() const
{
	return _status;
}
