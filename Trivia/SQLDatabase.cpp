#include "SQLDatabase.h"
#include <io.h>

bool SQLDatabase::runQuery(char * query)
{
	return sqlite3_exec(_db, query, nullptr, nullptr, nullptr) == SQLITE_OK;
}

bool SQLDatabase::open(const std::string & name)
{
	int doesFileExist = _access(name.c_str(), 0);
	int res = sqlite3_open(name.c_str(), &_db);
	if (res != SQLITE_OK)
	{
		_db = nullptr;
		return false;
	}
	if (!doesFileExist)
	{
		if (!runQuery("CREATE TABLE USERS (USERNAME TEXT PRIMARY KEY NOT NULL, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL)"))
		{
			sqlite3_close(_db);
			_db = nullptr;
			return false;
		}
		if (!runQuery("CREATE TABLE QUESTION (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, QUESTION TEXT NOT NULL, CORRECT_ANS TEXT NOT NULL, ANSWER2 TEXT NOT NULL, ANSWER3 TEXT NOT NULL, ANSWER4 TEXT NOT NULL)"))
		{
			sqlite3_close(_db);
			_db = nullptr;
			return false;
		}
		/*
		if (!runQuery(""))
		{
			sqlite3_close(_db);
			_db = nullptr;
			return false;
		}
		*/
	}
	return true;
}

bool SQLDatabase::login(const std::string & un, const std::string & p)
{
	static const char* QUERY = "GET * WHERE FROM USER WHERE USERNAME=? AND PASSWORD=?";
	const char* username = un.c_str();
	const char* password = p.c_str();
	bool exists = false;
	static auto callback = [](void* boolean, int len, const char **, const char**) -> int 
	{
		*((bool*)boolean) = true;
		return SQLITE_OK;
	};
	exec(QUERY, callback, &exists, nullptr, "TT", {username, password});
	return exists;
}

bool SQLDatabase::signup(const std::string & u, const std::string & p, const std::string & e)
{
	static const char* QUERY = "INSERT INTO USERS (USERNAME, PASSWORD, EMAIL) VALUES (?, ?, ?)";
	const char* username = u.c_str();
	const char* password = p.c_str();
	const char* email = e.c_str();
	return exec(QUERY, nullptr, nullptr, nullptr, "TTT", {username, password, email}) != SQLITE_OK;
}

int SQLDatabase::exec(const char * query, int(*callback)(void *, int, const char **, const char **), void * val, char ** errmsg, const char * types, std::vector<void*> args)
{
	const static auto writeNotNull = [](char** errMsg, const char* msg) {
		if (errMsg != nullptr)
		{
			int len = 0;
			for (len = 0; msg[len] != 0; len++);
			*errMsg = new char[len];
			for (len = 0; (*errMsg[len] = msg[len]) != 0; len++);
		}
	};
	sqlite3_stmt* stmt;
	const char *pzTest;
	int rc = sqlite3_prepare_v2(_db, query, strlen(query), &stmt, &pzTest);
	if (rc == SQLITE_OK)
	{
		for (int pos = 0; types[pos] != 0; pos++)
		{
			switch (types[pos])
			{
			case 'I':
			case 'i':
				rc = sqlite3_bind_int(stmt, pos + 1, *((int*)args[pos]));
				break;
			case 'D':
			case 'd':
				rc = sqlite3_bind_double(stmt, pos + 1, *((double*)args[pos]));
				break;
			case 'T':
			case 't':
			{
				char* text = *((char**)args[pos]);
				rc = sqlite3_bind_text(stmt, pos + 1, text, strlen(text), nullptr);
			}
			break;
			case 'S':
			case 's':
			{
				const char* text = ((std::string*)args[pos])->c_str();
				rc = sqlite3_bind_text(stmt, pos + 1, text, strlen(text), nullptr);
			}
			break;
			}
			if (rc != SQLITE_OK)
			{
				writeNotNull(errmsg, "Error while binding the values");
				sqlite3_finalize(stmt);
				return rc;
			}
		}
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			if (callback == nullptr)
				continue;
			int colNum = sqlite3_column_count(stmt);
			const char** text = new const char*[colNum];
			const char** names = new const char*[colNum];
			for (int i = 0; i < colNum; i++)
			{
				text[i] = (const char*)sqlite3_column_text(stmt, i);
				names[i] = (const char*)sqlite3_column_name(stmt, i);
			}
			rc = callback(val, colNum, text, names);
			delete text;
			delete names;
			if (rc != SQLITE_OK)
			{
				writeNotNull(errmsg, "Error while executing callback function");
				sqlite3_finalize(stmt);
				return rc;
			}
		}
		sqlite3_finalize(stmt);
	}
	return rc;
}

