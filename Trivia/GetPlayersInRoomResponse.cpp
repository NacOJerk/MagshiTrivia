#include "GetPlayersInRoomResponse.h"

GetPlayersInRoomResponse::GetPlayersInRoomResponse(vector<string> _players) : players(_players)
{
}

vector<string> GetPlayersInRoomResponse::getPlayers()
{
	return players;
}