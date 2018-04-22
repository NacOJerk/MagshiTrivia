#pragma once
#include <string>

class LoginRequest
{
	std::string _username;
	std::string _password;
public:
	LoginRequest(std::string, std::string);
	std::string getUsername();
	std::string getPassword();
};

