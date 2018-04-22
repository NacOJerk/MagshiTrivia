#pragma once
#include <vector>
#include <string>

using std::string;
using std::vector;

class GetPlayersInRoomResponse
{
private:
	vector<string> players;
public:
	GetPlayersInRoomResponse(vector<string>);
	vector<string> getPlayers();
};