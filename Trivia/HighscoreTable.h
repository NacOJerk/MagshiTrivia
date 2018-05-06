#pragma once

#include "IDatabase.h"
#include "Highscore.h"
#include <vector>

using std::vector;

class HighscoreTable
{
private:
	IDatabase& m_database;
public:
	HighscoreTable(IDatabase&);
	vector<Highscore> getHighscores();
	void addQuestionStat(const string& username, const unsigned int& time, const unsigned int& stupidityRate);
};