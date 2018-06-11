#pragma once

#include "Question.h"
#include <ctime>

typedef struct GameData
{
	//Question Related
	Question currentQuestion;
	unsigned int currentQuestionID;

	//Stat Related
	unsigned int currectAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;

	//Time Related
	std::time_t lastAnswer;
} GameData;