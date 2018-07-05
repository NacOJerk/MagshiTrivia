#pragma once
#include <vector>
#include <map>
#include <string>
#include "Question.h"
#include "consts.hpp"

class QuestionData
{
	Question _current;
	time_t _questionStart;
	std::vector<unsigned int> _randomized;
public:
	QuestionData();
	QuestionData(Question);
	StupidMeter getStuipedityRate(unsigned int) const;
	std::string getQuestion() const;
	std::vector<std::string> getAnswers() const;
	time_t getStartTime() const;
};