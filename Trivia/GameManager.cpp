#include "GameManager.h"

GameManager::GameManager(IDatabase & data) : m_database(data)
{
	_ids = 100;
}

GameManager::~GameManager()
{
	locked_container<std::vector<Game*>> _games = this->_games;
	std::vector<Game*>& games = _games;
	for (auto game : games)
	{
		delete game;
	}
}

Game * GameManager::getGame(const unsigned int & id)
{
	locked_container<std::vector<Game*>> _games = this->_games;
	std::vector<Game*>& games = _games;
	std::vector<Game*>::iterator itr = games.begin();
	for (; itr != games.end(); itr++)
	{
		if ((**itr) == id)
			break;
	}
	if (itr != games.end())
		return *itr;
	return nullptr;
}

Game & GameManager::createGame( Room & rom, RequestHandlerFactory& _fact)
{
	Game* game = new Game(rom.getAllUsers(), m_database.getQuestions(rom.getData().getAmountQuestions()), m_database, rom.getData().getTimePerQuestion(),_fact,*this,_ids++);
	locked_container<std::vector<Game*>> _games = this->_games;
	std::vector<Game*>& games = _games;
	games.push_back(game);
	return *game;
}

void GameManager::removeGame(Game & gm)
{
	locked_container<std::vector<Game*>> _games = this->_games;
	std::vector<Game*>& games = _games;
	Game* game = &gm;
	std::vector<Game*>::iterator itr = games.begin();
	for (; itr != games.end(); itr++)
	{
		if (*itr == game)
			break;
	}
	if (itr != games.end())
	{
		games.erase(itr);
		delete game;
	}
}
