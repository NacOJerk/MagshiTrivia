#pragma once

#include <string>
#include <vector>

class SendQuestionResponse
{
	std::string _question;
	std::vector<std::string> _answers;
	unsigned int _remaining;
public:
	SendQuestionResponse(std::string question, std::vector<std::string> answers, unsigned int remaining);
	std::string getQuestion() const;
	std::vector<std::string> getAnswers() const;
	unsigned int getRemainingQuestions() const;
};

