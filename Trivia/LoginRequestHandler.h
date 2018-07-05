#pragma once

#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
	//functions
public:
	LoginRequestHandler(LoginManager&, RequestHandlerFactory&);
	bool isRequestRelevant(Request) override;
	RequestResult handlRequest(Request, Client&) override;
private:
	RequestResult login(Request, Client&);
	RequestResult signup(Request, Client&);
};

