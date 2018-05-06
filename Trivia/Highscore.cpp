#include "Highscore.h"

Highscore::Highscore(unsigned int sc, string name) : score(sc), username(name)
{}

unsigned int Highscore::getScore()
{
	return score;
}

string Highscore::getUsername()
{
	return username;
}