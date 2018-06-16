#include "QuestionData.h"
#include <ctime>
#include <algorithm>

QuestionData::QuestionData(Question question) : _current(question), _questionStart(time(NULL))
{
	size_t possibilities = _current.getPossibleAnswers().size();
	for (int i = 0; i < possibilities; _randomized.push_back(i++));
	std::random_shuffle(_randomized.begin(), _randomized.end());
}

StupidMeter QuestionData::getStuipedityRate(unsigned int id) const
{
	StupidMeter meter = BRICK;
	if (id < _randomized.size())
	{
		switch (_randomized[id])
		{
		case 0:
			meter = GENIUS;
			break;
		case 1:
			meter = CHALLENGED;
			break;
		case 2:
			meter = DUMB;
			break;
		default:
		case 3:
			meter = BRICK;
			break;
		}
	}
	return meter;
}

std::string QuestionData::getQuestion() const
{
	return _current.getQuestion();
}

std::map<unsigned int, std::string> QuestionData::getAnswers() const
{
	std::map<unsigned int, std::string> questions;
	std::vector<std::string> quest = _current.getPossibleAnswers();
	for (size_t i = 0, len = _randomized.size(); i < len; i++)
	{
		questions[i] = quest[_randomized[i]];
	}
	return questions;
}

time_t QuestionData::getStartTime() const
{
	return _questionStart;
}
