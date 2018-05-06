#include "GetPlayersInRoomResponse.h"

GetPlayersInRoomResponse::GetPlayersInRoomResponse(vector<string> players) : players(players)
{
}

vector<string> GetPlayersInRoomResponse::getPlayers()
{
	return players;
}