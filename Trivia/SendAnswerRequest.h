#pragma once
class SendAnswerRequest
{
	unsigned int _answer;
public:
	SendAnswerRequest(unsigned int answer);
	unsigned int getAnswer() const;
};

