#pragma once
#include <string>

using std::string;

class RoomData
{
private:
	unsigned int id;
	string name;
	unsigned int maxPlayers;
	unsigned int timePerQuestion;
	bool isActive;
public:
	RoomData( string, unsigned int, unsigned int, bool);
	
	string getName();
	unsigned int getId();
	unsigned int getMaxPlayers();
	unsigned int getTimePerQuestion();
	bool getIsActive();

	void setIsActive(bool isActive);
};