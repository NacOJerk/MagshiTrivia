#pragma once
#include "IRequestHandler.h"

class IRequestHandler;

class RequestResult
{
	buffer _response;
	IRequestHandler* _newHandler;
public:
	RequestResult(buffer, IRequestHandler*);
	buffer getBuffer();
	IRequestHandler* getNewHandler();
};

