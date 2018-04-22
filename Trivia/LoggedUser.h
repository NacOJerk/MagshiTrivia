#pragma once
#include <string>
class LoggedUser
{
	std::string m_username;
public:
	LoggedUser(const std::string&);
	std::string getUsername() const;
};

