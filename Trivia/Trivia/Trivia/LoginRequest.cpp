#include "LoginRequest.h"

LoginRequest::LoginRequest(std::string username, std::string password) : _username(username), _password(password)
{}

std::string LoginRequest::getUsername()
{
	return _username;
}

std::string LoginRequest::getPassword()
{
	return _password;
}