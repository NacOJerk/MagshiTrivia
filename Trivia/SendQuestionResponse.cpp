#include "SendQuestionResponse.h"

SendQuestionResponse::SendQuestionResponse(std::string question, std::vector<std::string> answers, unsigned int remaining) : _question(question), _answers(answers), _remaining(remaining)
{
}

std::string SendQuestionResponse::getQuestion() const
{
	return _question;
}

std::vector<std::string> SendQuestionResponse::getAnswers() const
{
	return _answers;
}

unsigned int SendQuestionResponse::getRemainingQuestions() const
{
	return _remaining;
}
