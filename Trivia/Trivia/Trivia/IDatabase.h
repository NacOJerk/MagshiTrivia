#pragma once

#include <string>

class IDatabase
{
public:
	virtual bool login(const std::string&,const std::string&) = 0;
	virtual bool signup(const std::string&,const std::string&,const std::string&) = 0;
};