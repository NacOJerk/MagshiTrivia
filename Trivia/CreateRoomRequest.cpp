#include "CreateRoomRequest.h"

CreateRoomRequest::CreateRoomRequest(string _username, unsigned int _maxUsers, unsigned int _questionCount, unsigned int _answerTimeout) : username(_username), maxUsers(_maxUsers), questionCount(_questionCount), answerTimeout(_answerTimeout)
{}

string CreateRoomRequest::getUsername()
{
	return username;
}

unsigned int CreateRoomRequest::getMaxUsers()
{
	return maxUsers;
}

unsigned int CreateRoomRequest::getQuestionCount()
{
	return questionCount;
}

unsigned int CreateRoomRequest::getAnswerTimeout()
{
	return answerTimeout;
}