#pragma once
#include <string>

using std::string;

class RoomData
{
private:
	unsigned int id;
	string name;
	string maxPlayers;
	unsigned int timePerQuestion;
	bool isActive;
public:
	RoomData(unsigned int, string, string, unsigned int, bool);
	
	string getName();
	unsigned int getId();
	string getMaxPlayers();
	unsigned int getTimePerQuestion();
	bool getIsActive();

	void setIsActive(bool isActive);
};