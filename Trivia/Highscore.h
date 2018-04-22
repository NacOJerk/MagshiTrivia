#pragma once

#include "string"

using std::string;

class Highscore
{
private:
	unsigned int score;
	string username;
public:
	Highscore(unsigned int, string);
	unsigned int getScore();
	string getUsername();
};