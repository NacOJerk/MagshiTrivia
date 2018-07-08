#pragma once
#include <vector>

using std::string;
using std::vector;

class GetRoomStateResponse
{
private:
	unsigned int _status;
	bool _hasGameBegun;
	vector<string> _players;
	unsigned int _questionCount;
	unsigned int _answerTimeout;
	unsigned int _maxPlayers;
public:
	GetRoomStateResponse(const unsigned int& status, const bool& hasGameBegun, const vector<string> players, const unsigned int& questionCount, const unsigned int& answerTimeout, const unsigned int& maxPlayers);
	unsigned int getStatus() const;
	bool getHasGameBegun() const;
	void startGame();
	vector<string> getPlayers() const;
	unsigned int getQuestionCount() const;
	unsigned int getAnswerTimeout() const;
	unsigned int getMaxPlayers() const;
};