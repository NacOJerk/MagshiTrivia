#pragma once

#include "IRequestHandler.h"
#include "GameManager.h"
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"
#include "Game.h"

class Game;
class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
	LoggedUser& m_user;
	Game& m_game;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult submitAnswer(Request);
	RequestResult leaveGame(Request);
public:
	GameRequestHandler(Game&, LoggedUser&, RequestHandlerFactory&);
	bool isRequestRelevant(Request) override;
	RequestResult handlRequest(Request, Client&) override;
};

