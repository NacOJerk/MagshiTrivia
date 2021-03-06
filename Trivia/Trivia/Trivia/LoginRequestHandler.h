#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
public:
	LoginRequestHandler(LoginManager&, RequestHandlerFactory&);
	bool isRequestRelevant(Request) override;
	RequestResult handlRequest(Request) override;
private:
	RequestResult login(Request);
	RequestResult signup(Request);
};

