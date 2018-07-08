#include "GetPlayersInRoomResponse.h"

GetPlayersInRoomResponse::GetPlayersInRoomResponse(vector<string> _players, const unsigned int& maxPlayers) : players(_players), max_players(maxPlayers)
{
}

vector<string> GetPlayersInRoomResponse::getPlayers()
{
	return players;
}

unsigned int GetPlayersInRoomResponse::getMaxPlayers()
{
	return max_players;
}
