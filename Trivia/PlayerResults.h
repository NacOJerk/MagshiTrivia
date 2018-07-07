#pragma once
#include <string>

typedef struct PlayerResults 
{
	std::string username;

	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
} PlayerResults;
