#pragma once

#include <vector>
#include <map>
#include <ctime>
#include "QuestionData.h"
#include "LoggedUser.h"
#include "Question.h"
#include "GameData.h"
#include "PlayerResults.h"
#include "consts.hpp"
#include "../locked.hpp"

class Game
{
	//vars
	std::vector<Question> m_question;
	size_t _timeForQuestion;//In seconds
	size_t _currentQuestionID;
	QuestionData _currentQuestion;

	//locked vars
	//Only stuff that can be changed by other threads
	locked<std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>> m_players;//This sucks
	locked<bool> _running;

	//functions
	void runGame();//Thread managing the game
	bool lastQuestion();
	byte isRoundOver();//Returns 0 if not, 1 if time ran out or all users answered the question, 2 if only one user or less left
	void testAnswers();
	void finishGame();
	void sendNextQuestion();
public:
	Game(std::vector<std::reference_wrapper<LoggedUser>>, std::vector<Question>);
	
	void submitAnswer(LoggedUser&, unsigned int, time_t);
	void removePlayer(LoggedUser&);

	void stop();


};

