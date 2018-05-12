#pragma once
#include "IDatabase.h"
#include "LoggedUser.h"
#include "../locked.hpp"
#include <string>
#include <vector>

class LoginManager
{
	IDatabase& m_database;
	locked<std::vector<LoggedUser>> m_loggedUsers;
public:
	LoginManager(IDatabase&);//No need for destructor
	bool signup(const std::string&,const std::string&,const std::string&, SOCKET);
	bool login(const std::string&,const std::string&, SOCKET);
	LoggedUser getUser(const std::string&);
	void logout(const std::string&);
};

