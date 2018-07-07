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
	if (getQuestions(1).size() < 1)
	{
		addQuestion("Who made this game ?", "Shahar and Barr", "Shahar", "Barr", "Donald Trump");
		addQuestion("Mark Zuckerberg was one of the founders of which social networking site?", "Facebook", "Twitter", "Apple", "A Tree");
		addQuestion("Created in 2009, what was the first decentralized cryptocurrency?", "Bitcoin", "Ethereum", "Dollar", "MD5");
		addQuestion("Who wrote Harry Potter ?", "J. K. Rowling", "Stephen Edwin King", "Barak Obama", "iPhone X");
		addQuestion("When talking about computer memory, what does the acronym ROM stand for?", "Read-only memory", "Random Access Memory", "Run On Me", "Mario Oddesy Runner");
		addQuestion("What does wabba laba dub dub mean?", "I am in great pain, please help me", "I am having a ton of fun join me", "NOTHING", "SEND COOKIES");
		addQuestion("In a photo editing program, what do the letters RGB stand for?", "Red, Green & Blue", "Run, Gain, Breath", "Raiding, Gaining, Balancing", "ROBERT SMITH");
		addQuestion("HTML and CSS are computer languages used to create what?", "Websites", "Programs", "CDs", "Quantom Computers !");
		addQuestion("Which monster is blue ?", "COOKIE MONSTER !", "Gremlin", "Chupacabra", "Banshee");
		addQuestion("In what year was the first Apple computer released?", "1976", "1996", "2006", "1946");
		addQuestion("In cooking, margarine is used as a substitute for what ingredient?", "Butter", "Sugar", "Honey", "COOKIES");
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
	const static char* QUERY = "SELECT WINS/ROOMS*1.0 FROM ROOM_STATS WHERE USER=?";
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

std::vector<Question> SQLDatabase::getQuestions(const unsigned int & _amount)
{
	const static char* QUERY = "SELECT QUESTION, CORRECT_ANS, ANSWER2, ANSWER3, ANSWER4 FROM QUESTION ORDER BY RANDOM() LIMIT ?";
	unsigned int amount = _amount;
	std::vector<Question> questions;
	const static auto callback = [](void* ques, int len, const char ** data, const char**) -> int
	{
		std::string question = string(data[0]);
		std::string currectAnswer = string(data[1]);
		((std::vector<Question>*)ques)->push_back(Question(question, currectAnswer, { string(data[2]), string(data[3]), string(data[4]) }));
		return SQLITE_OK;
	};
	exec(QUERY, callback, &questions, nullptr, "I", { &amount });
	return questions;
}

void SQLDatabase::addQuestion(const std::string & question, const std::string & currAns, const std::string & wAns2, const std::string & wAns3, const std::string & wAns4)
{
	const static char* QUERY = "INSERT INTO QUESTION (QUESTION, CORRECT_ANS, ANSWER2, ANSWER3, ANSWER4) VALUES (?, ?, ?, ?, ?)";
	const char* quest = question.c_str();
	const char* ans1 = currAns.c_str();
	const char* ans2 = wAns2.c_str();
	const char* ans3 = wAns3.c_str();
	const char* ans4 = wAns4.c_str();
	exec(QUERY, nullptr, nullptr, nullptr, "TTTTT", { &quest, &ans1, &ans2, &ans3, &ans4 });
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

