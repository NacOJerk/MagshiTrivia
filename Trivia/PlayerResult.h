#pragma once

#include <string>

typedef struct PlayerResult
{
	std::string username;
	unsigned int currectAnswers;
	unsigned int wrongAnswers;
	unsigned int averageTime;
} PlayerResult;