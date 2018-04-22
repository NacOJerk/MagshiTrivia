#include "SignupRequest.h"

SignupRequest::SignupRequest(std::string username, std::string password, std::string email) : _username(username), _password(password), _email(email)
{}

std::string SignupRequest::getUsername()
{
	return _username;
}

std::string SignupRequest::getPassword()
{
	return _password;
}

std::string SignupRequest::getEmail()
{
	return _email;
}