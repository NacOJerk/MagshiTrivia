#include "HighscoreResponse.h"

HighscoreResponse::HighscoreResponse(unsigned int status, vector<Highscore> highscores) : status(status), highscores(highscores)
{}

unsigned int HighscoreResponse::getStatus()
{
	return status;
}

vector<Highscore> HighscoreResponse::getHighscores()
{
	return highscores;
}