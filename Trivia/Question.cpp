#include "Question.h"

Question::Question(std::string question, std::string rightAnswer, std::vector<std::string> wrongAnswers) : m_question(question), m_answers()
{
	m_answers.push_back(rightAnswer);
	m_answers.insert(m_answers.end(), wrongAnswers.begin(), wrongAnswers.end());
}

Question::Question(std::string question, std::string rightAnswer) : Question(question, rightAnswer, std::vector<std::string>())
{
}

void Question::addWrongAnswer(std::string ans)
{
	m_answers.push_back(ans);
}

std::string Question::getQuestion() const
{
	return m_question;
}

std::vector<std::string> Question::getPossibleAnswers() const
{
	return m_answers;
}

std::string Question::getRightAnswer() const
{
	return m_answers[0];
}


