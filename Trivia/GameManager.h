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
	RequestHandlerFactory& _fact;
	IDatabase& m_database;
	locked<std::vector<Game*>> _games;
	unsigned int _ids;
public:
	GameManager(IDatabase&, RequestHandlerFactory&);
	~GameManager();
	Game& createGame(Room&);
	void removeGame(Game&);
};

