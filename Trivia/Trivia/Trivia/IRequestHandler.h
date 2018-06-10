#pragma once
#include "Request.h"
#include "RequestResult.h"

class RequestResult;

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(Request) = 0;
	virtual RequestResult handlRequest(Request) = 0;
};