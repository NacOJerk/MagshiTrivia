#include "HighscoreTable.h"

HighscoreTable::HighscoreTable(IDatabase& db) : m_database(db)
{}

vector<Highscore> HighscoreTable::getHighscores()
{
	return m_database.getHighscores(10);
}

void HighscoreTable::addQuestionStat(const string& username, const unsigned int& time, const unsigned int& stupidityRate)
{
	m_database.addQuestionStat(username, time, stupidityRate);
}

float HighscoreTable::getWinRate(const string & username)
{
	return m_database.getWinRate(username);
}

float HighscoreTable::getSuccessRate(const string & username)
{
	return m_database.getSuccessRate(username);
}

float HighscoreTable::getStuipdityRate(const string & username)
{
	return m_database.getStuipidityRate(username);
}

float HighscoreTable::getAverageTime(const string & username)
{
	return m_database.getAverageTime(username);
}
