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
#include "IDatabase.h"
#include "RequestHandlerFactory.h"
#include "GameManager.h"

class GameManager;

class Game
{
	//vars
	const unsigned int _id;
	IDatabase& _base;
	RequestHandlerFactory&  _factory;
	GameManager& _manager;
	std::vector<Question> m_question;
	size_t _timeForQuestion;//In seconds
	size_t _currentQuestionID;// starting value -1
	QuestionData _currentQuestion;

	//locked vars
	//Only stuff that can be changed by other threads
	locked<std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>>> m_players;//This sucks
	locked<bool> _running;
	std::thread _tr;

	//functions
	void runGame();//Thread managing the game
	bool lastQuestion();
	byte isRoundOver();//Returns 0 if not, 1 if time ran out or all users answered the question, 2 if only one user or less left
	void testAnswers();
	void finishGame();
	void sendNextQuestion();
	void sendHome();
	void stop();

public:
	Game(std::vector<std::reference_wrapper<LoggedUser>>, std::vector<Question>, IDatabase&, size_t, RequestHandlerFactory&, GameManager&, const unsigned int id);
	~Game();
	bool operator==(const Game& b) const;
	void start();
	void submitAnswer(LoggedUser&, unsigned int, time_t);
	void removePlayer(LoggedUser&);



};

