#pragma once

#include "LoggedUser.h"
#include "RoomManager.h"
#include "HighscoreTable.h"
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
private:
	LoggedUser& m_users;
	RoomManager& m_roomManager;
	HighscoreTable& m_highscoreTable;
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult signout(Request);
	RequestResult getRooms(Request);
	RequestResult getPlayersInRoom(Request);
	RequestResult getHighscores(Request);
	RequestResult joinRoom(Request);
	RequestResult createRoom(Request);
	RequestResult getStats(Request);

public:
	MenuRequestHandler(LoggedUser&, RoomManager&, HighscoreTable&, LoginManager&, RequestHandlerFactory&);
	bool isRequestRelevant(Request) override;
	RequestResult handlRequest(Request, Client&) override;
};