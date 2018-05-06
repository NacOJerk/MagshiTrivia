#pragma once

#include <string>

using std::string;

class CreateRoomRequest
{
private:
	string username;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
public:
	CreateRoomRequest(string, unsigned int, unsigned int, unsigned int);
	string getUsername();
	unsigned int getMaxUsers();
	unsigned int getQuestionCount();
	unsigned int getAnswerTimeout();
};