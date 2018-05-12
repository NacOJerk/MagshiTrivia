#pragma once
#include <vector>
#include "RoomData.h"
#include "LoggedUser.h"

using std::vector;

class Room
{
private:
	RoomData m_metadata;
	vector<std::reference_wrapper<LoggedUser>> m_users;
public:
	Room();
	Room(RoomData, vector<std::reference_wrapper<LoggedUser>>);
	void addUser(LoggedUser&);
	void removeUser(string);
	vector<std::reference_wrapper<LoggedUser>>& getAllUsers();
	RoomData getData();
};