#pragma once

#include <vector>
#include <map>
#include "LoggedUser.h"
#include "Question.h"
#include "GameData.h"
#include "PlayerResults.h"

class Game
{
	std::vector<Question> m_question;
	std::map<std::reference_wrapper<LoggedUser>, GameData, std::less<const LoggedUser>> m_players;
public:
	Game(std::vector<std::reference_wrapper<LoggedUser>>, std::vector<Question>);
	Question getQuestion(LoggedUser&);
	void submitAnswer(LoggedUser&, std::string, std::time_t);
	void removePlayer(LoggedUser&);

	bool isGameOver() const;
	std::vector<PlayerResults> getScores();

};

