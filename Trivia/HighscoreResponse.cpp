#include "HighscoreResponse.h"

HighscoreResponse::HighscoreResponse(unsigned int status, vector<HighscoreTable> highscores) : status(status), highscores(highscores)
{}

unsigned int HighscoreResponse::getStatus()
{
	return status;
}

vector<HighscoreTable> HighscoreResponse::getHighscores()
{
	return highscores;
}