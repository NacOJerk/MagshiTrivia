#pragma once

#include "Game.h"

class Game;

struct UserRoomData
{
	bool loggedIn;
	unsigned int id;
	bool isAdmin;
	Game* game;
};