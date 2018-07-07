#pragma once
#include <string>
#include <vector>
#include "../sqlite3.h"
#include "IDatabase.h"

class SQLDatabase :
	public IDatabase
{
	int i = 0;
	sqlite3* _db;
	int exec(const char* query, int(*callback)(void*, int, const char **, const char **), void* val, char** errmsg, const char* types, std::vector<void*> args);
	bool runQuery(char* query);
public:
	~SQLDatabase();
	bool open(const std::string&);//filename
	bool login(const std::string&, const std::string&) override;
	bool signup(const std::string&, const std::string&, const std::string&) override;
	void addHighscore(const std::string&, const unsigned int&) override;
	std::vector<Highscore> getHighscores(const unsigned int&) override;
	void addQuestionStat(const std::string&, const unsigned int&, const unsigned int&) override;
	float getAverageTime(const std::string&) override;
	float getSuccessRate(const std::string&) override;
	float getStuipidityRate(const std::string&) override;
	void addGame(const std::string&, const bool&) override;
	float getWinRate(const std::string&) override;
	std::vector<Question> getQuestions(const unsigned int&) override;
	void addQuestion(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&) override;
};

