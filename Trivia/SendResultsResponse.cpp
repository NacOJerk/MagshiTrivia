#include "SendResultsResponse.h"

SendResultsResponse::SendResultsResponse(unsigned int position, std::vector<PlayerResult> results) : _position(position), _results(results)
{
}

unsigned int SendResultsResponse::getPosition() const
{
	return _position;
}

std::vector<PlayerResult> SendResultsResponse::getResults() const
{
	return _results;
}
