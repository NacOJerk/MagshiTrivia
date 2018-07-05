#pragma once

#include "IRequestHandler.h"
#include "GameManager.h"
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
	Game& m_game;
	LoggedUser& m_user;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult submitAnswer(Request);
	RequestResult leaveGame(Request);
public:
	GameRequestHandler(Game&, LoggedUser&, RequestHandlerFactory&);
	bool isRequestRelevant(Request) override;
	RequestResult handlRequest(Request, Client&) override;
};

