#pragma once
#include "Client.h"
#include "Request.h"
#include "RequestResult.h"

class RequestResult;
class Client;

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(Request) = 0;
	virtual RequestResult handlRequest(Request, Client&) = 0;
};