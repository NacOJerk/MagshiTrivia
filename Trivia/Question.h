#pragma once

#include <string>
#include <vector>

class Question
{
	std::string m_question;
	std::vector<std::string> m_answers;
public:
	Question(std::string, std::string, std::vector<std::string>);
	Question(std::string, std::string);
	void addWrongAnswer(std::string);
	std::string getQuestion() const;
	std::vector<std::string> getPossibleAnswers() const;
	std::string getRightAnswer() const;  
};

