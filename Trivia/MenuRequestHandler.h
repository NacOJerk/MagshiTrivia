#pragma once

#include "LoggedUser.h"
#include "RoomManager.h"
#include "HighscoreTable.h"
#include "RequestHandlerFactory.h"

class MenuRequestHandler
{
private:
	LoggedUser m_users;
	RoomManager m_roomManager;
	HighscoreTable m_highscoreTable;
	RequestHandlerFactory m_handlerFactory;

	RequestResult signout(Request);
	RequestResult getRooms(Request);
	RequestResult getPlayersInRoom(Request);
	RequestResult getHighscores(Request);
	RequestResult joinRoom(Request);
	RequestResult createRoom(Request);

public:
	bool isRequestRelevant(Request);
	RequestResult handleRequest(Request);
};