#pragma once

#include "PlayerResult.h"
#include <vector>

class SendResultsResponse
{
	unsigned int _position;
	std::vector<PlayerResult> _results;
public:
	SendResultsResponse(unsigned int position, std::vector<PlayerResult> results);
	unsigned int getPosition() const;
	std::vector<PlayerResult> getResults() const;
};

