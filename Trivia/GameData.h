#pragma once

#include "Question.h"

typedef struct GameData
{
	//Answer Related
	bool answered;
	unsigned int answerID;
	time_t questionAnswer;

	//Stat Related
	unsigned int currectAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
	
} GameData;