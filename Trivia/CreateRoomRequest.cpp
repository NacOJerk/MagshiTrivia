#include "CreateRoomRequest.h"

CreateRoomRequest::CreateRoomRequest(string username, unsigned int maxUsers, unsigned int questionCount, unsigned int answerTimeout) : username(username), maxUsers(maxUsers), questionCount(questionCount), answerTimeout(answerTimeout)
{}

string CreateRoomRequest::getUsername()
{
	return username;
}

unsigned int CreateRoomRequest::getMaxUsers()
{
	return maxUsers;
}