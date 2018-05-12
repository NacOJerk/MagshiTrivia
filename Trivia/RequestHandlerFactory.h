#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "RoomManager.h"
#include "HighscoreTable.h"
#include "MenuRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	HighscoreTable m_highscoreTable;
	IDatabase& _database;
public:
	RequestHandlerFactory(IDatabase&);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser);
	LoginManager* getLoginManager();
	RoomManager* getRoomManager();
	HighscoreTable* getHighscoreTable();
};

