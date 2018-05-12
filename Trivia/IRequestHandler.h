#pragma once
#include <WinSock2.h>
#include "Request.h"
#include "RequestResult.h"

class RequestResult;

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(Request) = 0;
	virtual RequestResult handlRequest(Request, SOCKET) = 0;
};