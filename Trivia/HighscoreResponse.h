#pragma once
#include <vector>
#include "HighscoreTable.h"

using std::vector;

class HighscoreResponse
{
private:
	unsigned int status;
	vector<HighscoreTable> highscores;
public:
	HighscoreResponse(unsigned int, vector<HighscoreTable>);
	unsigned int getStatus();
	vector<HighscoreTable> getHighscores();
};