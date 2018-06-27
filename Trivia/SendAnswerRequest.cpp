#include "SendAnswerRequest.h"

SendAnswerRequest::SendAnswerRequest(unsigned int answer) : _answer(answer)
{
}

unsigned int SendAnswerRequest::getAnswer() const
{
	return _answer;
}
