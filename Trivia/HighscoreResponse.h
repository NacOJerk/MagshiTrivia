#pragma once
#include <vector>
#include "HighscoreTable.h"

using std::vector;

class HighscoreResponse
{
private:
	unsigned int status;
	vector<Highscore> highscores;
public:
	HighscoreResponse(unsigned int, vector<Highscore>);
	unsigned int getStatus();
	vector<Highscore> getHighscores();
};