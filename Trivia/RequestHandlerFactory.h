#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "RoomManager.h"
#include "HighscoreTable.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameManager.h"
#include "GameRequestHandler.h"

class GameManager;
class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory
{
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	GameManager m_gameManager;
	HighscoreTable m_highscoreTable;
	IDatabase& _database;
public:
	RequestHandlerFactory(IDatabase&);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser&);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser&, Room&);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser&, Room&);
	GameRequestHandler* createGameRequestHandler(LoggedUser&, Game&);
	LoginManager* getLoginManager();
	RoomManager* getRoomManager();
	HighscoreTable* getHighscoreTable();
	GameManager* getGameManager();
};

