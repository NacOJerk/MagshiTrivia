#include "SQLDatabase.h"
#include <io.h>


bool SQLDatabase::runQuery(char * query)
{
	return sqlite3_exec(_db, query, nullptr, nullptr, nullptr) == SQLITE_OK;
}

SQLDatabase::~SQLDatabase()
{
	sqlite3_close(_db);
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
	if (doesFileExist == -1)
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
		if (!runQuery("CREATE TABLE HIGHSCORE (ID INTEGER PRIMARY KEY NOT NULL, USER TEXT NOT NULL, HIGHSCORE INTEGER NOT NULL, FOREIGN KEY (USER) REFERENCES USERS(USENAME));"))
		{
			sqlite3_close(_db);
			_db = nullptr;
			return false;
		}
		if (!runQuery("CREATE TABLE QUESTION_STATS (USER TEXT PRIMARY KEY NOT NULL, TIME INTEGER NOT NULL, QUESTIONS INTEGER NOT NULL, CORRECT INTEGER NOT NULL, STUIPED INTEGER NOT NULL, FOREIGN KEY (USER) REFERENCES USERS(USERNAME));"))
		{
			sqlite3_close(_db);
			_db = nullptr;
			return false;
		}
		if (!runQuery("CREATE TABLE ROOM_STATS (USER TEXT PRIMARY KEY NOT NULL, WINS INTEGER NOT NULL, ROOMS INTEGER NOT NULL, FOREIGN KEY (USER) REFERENCES USERS(USERNAME));"))
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
	static const char* QUERY = "SELECT * FROM USERS WHERE USERNAME=? AND PASSWORD=?";
	const char* username = un.c_str();
	const char* password = p.c_str();
	bool exists = false;
	static auto callback = [](void* boolean, int len, const char **, const char**) -> int 
	{
		*((bool*)boolean) = true;
		return SQLITE_OK;
	};
	exec(QUERY, callback, &exists, nullptr, "TT", {&username, &password});
	return exists;
}

bool SQLDatabase::signup(const std::string & u, const std::string & p, const std::string & e)
{
	static const char* EXIST_CHECK = "SELECT * FROM USERS WHERE USERNAME=?";
	const char* username = u.c_str();
	const char* password = p.c_str();
	const char* email = e.c_str();
	bool exists = false;
	static auto callback = [](void* boolean, int len, const char **, const char**) -> int
	{
		*((bool*)boolean) = true;
		return SQLITE_OK;
	};
	exec(EXIST_CHECK, callback, &exists, nullptr, "T", { &username });
	if (exists)
		return false;
	static const char* QUERY = "INSERT INTO USERS (USERNAME, PASSWORD, EMAIL) VALUES (?, ?, ?)";
	return !exec(QUERY, nullptr, nullptr, nullptr, "TTT", {&username, &password, &email});
}

void SQLDatabase::addHighscore(const std::string & u, const unsigned int & score)
{
	const static char* QUERY = "INSERT INTO HIGHSCORE (USER, HIGHSCORE) VALUES (?, ?)";
	const char* username = u.c_str();
	unsigned int scor = score;
	exec(QUERY, nullptr, nullptr, nullptr, "TI", { &username, &scor });
}

std::vector<Highscore> SQLDatabase::getHighscores(const unsigned int & amount)
{
	const static char* QUERY = "SELECT USER, HIGHSCORE FROM HIGHSCORE ORDER BY HIGHSCORE DESC LIMIT ?";
	std::vector<Highscore> highscores;
	const static auto callback = [](void* vec, int, const char** data, const char**) -> int 
	{
		((std::vector<Highscore>*)vec)->push_back(Highscore(atoi(data[1]), std::string(data[0])));
		return SQLITE_OK;
	};
	unsigned int amoun = amount;
	exec(QUERY, callback, &highscores, nullptr, "I", { &amoun });
	return highscores;
}

void SQLDatabase::addQuestionStat(const std::string & username, const unsigned int & time, const unsigned int & stuiped_scores)
{
	const static char* EXISTS = "SELECT * FROM QUESTION_STATS WHERE USER=?";
	const static char* ADD = "INSERT INTO QUESTION_STATS (USER, TIME, QUESTIONS, CORRECT, STUIPED) VALUES (?, ?, 1, ?, ?)";
	const static char* UPDATE = "UPDATE QUESTION_STATS SET TIME = TIME + ?, QUESTIONS = QUESTIONS + 1, CORRECT = CORRECT + ?, STUIPED = STUIPED + ? WHERE USER=?";
	const char* user = username.c_str();
	int correct = !stuiped_scores ? 1 : 0;
	unsigned int tim = time;
	unsigned int stuiped = stuiped_scores;
	bool exists = false;
	const static auto callback = [](void* boolean, int len, const char **, const char**) -> int
	{
		*((bool*)boolean) = true;
		return SQLITE_OK;
	};
	exec(EXISTS, callback, &exists, nullptr, "T", { &user });
	if (!exists)
		exec(ADD, nullptr, nullptr, nullptr, "TIII", { &user, &tim, &correct, &stuiped });
	else
		exec(UPDATE, nullptr, nullptr, nullptr, "IIIT", {&tim, &correct, &stuiped, &user});
}

float SQLDatabase::getAverageTime(const std::string & u)
{
	const char* QUERY = "SELECT TIME/QUESTIONS*1.0 FROM QUESTION_STATS WHERE USER=?";
	const char* username = u.c_str();
	float storer = -1;
	const static auto callback = [](void* store, int len, const char ** data, const char**) -> int
	{
		*((bool*)store) = atof(data[0]);
		return SQLITE_OK;
	};
	exec(QUERY, callback, &storer, nullptr, "T", { &username });
	return storer;
}

float SQLDatabase::getSuccessRate(const std::string & u)
{
	const char* QUERY = "SELECT CORRECT/QUESTIONS*1.0 FROM QUESTION_STATS WHERE USER=?";
	const char* username = u.c_str();
	float storer = -1;
	const static auto callback = [](void* store, int len, const char ** data, const char**) -> int
	{
		*((bool*)store) = atof(data[0]) * 100;
		return SQLITE_OK;
	};
	exec(QUERY, callback, &storer, nullptr, "T", { &username });
	return storer;
}

float SQLDatabase::getStuipidityRate(const std::string & u)
{
	const char* QUERY = "SELECT STUIPED/QUESTIONS*1.0 FROM QUESTION_STATS WHERE USER=?";
	const char* username = u.c_str();
	float storer = -1;
	const static auto callback = [](void* store, int len, const char ** data, const char**) -> int
	{
		*((bool*)store) = atof(data[0]) * 100;
		return SQLITE_OK;
	};
	exec(QUERY, callback, &storer, nullptr, "T", { &username });
	return storer;
}

void SQLDatabase::addGame(const std::string & username, const bool & win)
{
	const static char* EXISTS = "SELECT * FROM ROOM_STATS WHERE USER=?";
	const static char* ADD = "INSERT INTO ROOM_STATS (USER, WINS, ROOMS) VALUES (?, ?, 1)";
	const static char* UPDATE = "UPDATE ROOM_STATS SET WINS = WINS + ?, ROOMS = ROOMS + 1 WHERE USER = ?";
	const char* user = username.c_str();
	unsigned int add = win ? 1 : 0;
	bool exists = false;
	const static auto callback = [](void* boolean, int len, const char **, const char**) -> int
	{
		*((bool*)boolean) = true;
		return SQLITE_OK;
	};
	exec(EXISTS, callback, &exists, nullptr, "T", { &user });
	if (!exists)
		exec(ADD, nullptr, nullptr, nullptr, "TI", { &user, &add });
	else
		exec(UPDATE, nullptr, nullptr, nullptr, "IT", { &add, &user });
}

float SQLDatabase::getWinRate(const std::string & u)
{
	const char* QUERY = "SELECT WINS/ROOMS*1.0 FROM ROOM_STATS WHERE USER=?";
	const char* username = u.c_str();
	float storer = -1;
	const static auto callback = [](void* store, int len, const char ** data, const char**) -> int
	{
		*((bool*)store) = atof(data[0]) * 100;
		return SQLITE_OK;
	};
	exec(QUERY, callback, &storer, nullptr, "T", { &username });
	return storer;
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

