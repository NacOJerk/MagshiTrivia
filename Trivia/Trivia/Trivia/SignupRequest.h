#pragma once
#include <string>

class SignupRequest
{
	std::string _username;
	std::string _password;
	std::string _email;
public:
	SignupRequest(std::string, std::string, std::string);
	std::string getUsername();
	std::string getPassword();
	std::string getEmail();
};

