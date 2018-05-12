#include "HighscoreResponse.h"

HighscoreResponse::HighscoreResponse(unsigned int _status, vector<Highscore> _highscores) : status(_status), highscores(_highscores)
{}

unsigned int HighscoreResponse::getStatus()
{
	return status;
}

vector<Highscore> HighscoreResponse::getHighscores()
{
	return highscores;
}