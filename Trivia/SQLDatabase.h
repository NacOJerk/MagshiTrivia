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
};

