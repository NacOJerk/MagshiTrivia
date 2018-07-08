#pragma once
#include <vector>
#include <string>

using std::string;
using std::vector;

class GetPlayersInRoomResponse
{
private:
	vector<string> players;
	unsigned int max_players;
public:
	GetPlayersInRoomResponse(vector<string>, const unsigned int&);
	vector<string> getPlayers();
	unsigned int getMaxPlayers();
};