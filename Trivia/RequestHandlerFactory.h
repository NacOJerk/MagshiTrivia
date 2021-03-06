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

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;
class GameManager;
class Game;

class RequestHandlerFactory
{
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	GameManager* m_gameManager;
	HighscoreTable m_highscoreTable;
	IDatabase& _database;
public:
	RequestHandlerFactory(IDatabase&);
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser&);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser&, Room&);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser&, Room&);
	GameRequestHandler* createGameRequestHandler(LoggedUser&, Game&);
	IDatabase& getDatabase();
	LoginManager* getLoginManager();
	RoomManager* getRoomManager();
	HighscoreTable* getHighscoreTable();
	GameManager* getGameManager();
};

