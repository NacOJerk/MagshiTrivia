#include "RoomData.h"
#include "RoomManager.h"

RoomData::RoomData()
{
}

RoomData::RoomData(string name, unsigned int maxPlayers, unsigned int time, unsigned int questionAmo, bool isActive) : name(name), maxPlayers(maxPlayers), timePerQuestion(time), isActive(isActive), amountQuestions(questionAmo)
{
	id = RoomManager::generateId();
}

string RoomData::getName()
{
	return name;
}

unsigned int RoomData::getId()
{
	return id;
}

unsigned int RoomData::getMaxPlayers()
{
	return maxPlayers;
}

unsigned int RoomData::getTimePerQuestion()
{
	return timePerQuestion;
}

unsigned int RoomData::getAmountQuestions()
{
	return amountQuestions;
}

bool RoomData::getIsActive()
{
	return isActive;
}

void RoomData::setIsActive(bool isActive)
{
	this->isActive = isActive;
}