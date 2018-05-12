#include "Highscore.h"

Highscore:: Highscore() : Highscore(0, "empty")
{
}

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