#pragma once
#include "IDatabase.h"
#include "LoggedUser.h"
#include "../locked.hpp"
#include <string>
#include <vector>

class LoggedUser;
class Client;

class LoginManager
{
	IDatabase& m_database;
	locked<std::vector<LoggedUser*>> m_loggedUsers;
public:
	LoginManager(IDatabase&);//No need for destructor
	bool signup(const std::string&,const std::string&,const std::string&, Client&);
	bool login(const std::string&,const std::string&, Client&);
	LoggedUser* getUser(const std::string&);
	void logout(const std::string&);
};