#pragma once

#include "Room.h"
#include "../locked.hpp"
#include "Game.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"
#include <vector>

class RequestHandlerFactory;
class Game;

class GameManager
{
	IDatabase& m_database;
	locked<std::vector<Game*>> _games;
	unsigned int _ids;
public:
	GameManager(IDatabase&);
	~GameManager();
	Game* getGame(const unsigned int&);
	Game& createGame(Room&, RequestHandlerFactory&);
	void removeGame(Game&);
};

