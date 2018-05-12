#pragma once
#include <vector>
#include "RoomData.h"
#include "LoggedUser.h"

using std::vector;

class Room
{
private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;
public:
	Room();
	Room(RoomData, vector<LoggedUser>);
	void addUser(LoggedUser);
	void removeUser(string);
	vector<LoggedUser> getAllUsers();
	RoomData getData();
};