#pragma once

#include <string>
#include <vector>
#include "Highscore.h"

class IDatabase
{
public:
	virtual bool login(const std::string&,const std::string&) = 0;
	virtual bool signup(const std::string&,const std::string&,const std::string&) = 0;
	virtual void addHighscore(const std::string&, const unsigned int&) = 0;
	virtual std::vector<Highscore> getHighscores(const unsigned int&) = 0;
	virtual void addQuestionStat(const std::string&, const unsigned int&, const unsigned int&) = 0;
	virtual float getAverageTime(const std::string&) = 0;
	virtual float getSuccessRate(const std::string&) = 0;
	virtual float getStuipidityRate(const std::string&) = 0;
	virtual void addGame(const std::string&, const bool&) = 0;
	virtual float getWinRate(const std::string&) = 0;
};