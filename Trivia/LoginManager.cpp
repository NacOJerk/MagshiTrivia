#include "LoginManager.h"

LoginManager::LoginManager(IDatabase& data) : m_database(data), m_loggedUsers(new std::vector<LoggedUser>)
{}

bool LoginManager::signup(const std::string& username, const std::string& password, const std::string& email, SOCKET socket)
{
	bool result = false;
	if (result = m_database.signup(username, password, email))
	{
		std::vector<LoggedUser>* users = m_loggedUsers;
		users = m_loggedUsers;
		users->push_back(LoggedUser(username, socket));
		users = nullptr;
		m_loggedUsers();

	}
	return result;
}

bool LoginManager::login(const std::string& username, const std::string& password, SOCKET socket)
{
	std::vector<LoggedUser>* users = m_loggedUsers;
	std::vector<LoggedUser>::iterator it;
	for (it = users->begin(); it != users->end(); ++it) {
		if (it->getUsername() == username)
			break;
	}
	bool userExists = it != users->end();
	users = nullptr;
	m_loggedUsers();
	if (userExists)
		return false;
	bool logged = m_database.login(username, password);
	if (logged)
	{
		users = m_loggedUsers;
		users->push_back(LoggedUser(username, socket));
		users = nullptr;
		m_loggedUsers();
	}
	return logged;
}

LoggedUser LoginManager::getUser(const std::string & username)
{
	std::vector<LoggedUser>* users = m_loggedUsers;
	std::vector<LoggedUser>::iterator it;
	for (it = users->begin(); it != users->end(); ++it) {
		if (it->getUsername() == username)
			break;
	}
	bool userExists = it != users->end();

	if (!userExists)
	{
		users = nullptr;
		m_loggedUsers();
		throw std::exception("Couldn't find user");
	}
	LoggedUser usr = *it;
	users = nullptr;
	m_loggedUsers();
	return usr;
}

void LoginManager::logout(const std::string& name)
{
	std::vector<LoggedUser>* users = m_loggedUsers;
	std::vector<LoggedUser>::iterator it;
	for (it = users->begin(); it != users->end(); ++it) {
		if (it->getUsername() == name)
			break;
	}
	if (it != users->end())
		users->erase(it);
	users = nullptr;
	m_loggedUsers();
}