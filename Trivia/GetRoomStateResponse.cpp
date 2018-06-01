#include "GetRoomStateResponse.h"

GetRoomStateResponse::GetRoomStateResponse(const unsigned int status, const bool hasGameBegun, const vector<string> players, const unsigned int questionCount, const unsigned int answerTimeout) : _status(status), _hasGameBegun(hasGameBegun), _players(players), _questionCount(questionCount), _answerTimeout(answerTimeout)
{}

unsigned int GetRoomStateResponse::getStatus() const
{
	return _status;
}

bool GetRoomStateResponse::getHasGameBegun() const
{
	return _hasGameBegun;
}

void GetRoomStateResponse::startGame()
{
	_hasGameBegun = true;
}

vector<string> GetRoomStateResponse::getPlayers() const
{
	return _players;
}

unsigned int GetRoomStateResponse::getQuestionCount() const
{
	return _questionCount;
}

unsigned int GetRoomStateResponse::getAnswerTimeout() const
{
	return _answerTimeout;
}