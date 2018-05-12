#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "LoginResponse.h"
#include "SignupResponse.h"
#include <exception>
#include <utility>
#include <regex>

#define EMAIL_REGEX "[a-zA-Z0-9!#$%&'\*\+-/=\?\^_`{\|}~]+@[a-zA-Z0-9!#$%&'\*\+-/=\?\^_`{\|}~]+\.[a-zA-Z0-9!#$%&'\*\+-/=\?\^_`{\|}~]+"
#define PHONE_REGEX "\d{2,3}-?\d{7}"

LoginRequestHandler::LoginRequestHandler(LoginManager & mang, RequestHandlerFactory & facto) : m_loginManager(mang), m_handlerFactory(facto)
{
}

bool LoginRequestHandler::isRequestRelevant(Request request)
{
	RequestId id = request.getID();
	return id == LOGIN_REQUEST || id == SIGNUP_REQUEST;
}

RequestResult LoginRequestHandler::handlRequest(Request request, SOCKET sock)
{
	switch (request.getID())
	{
	case LOGIN_REQUEST:
		return login(request, sock);
	case SIGNUP_REQUEST:
		return signup(request, sock);
	}
	throw std::exception("Couldn't handle packet");
}

RequestResult LoginRequestHandler::login(Request req, SOCKET sock)
{
	LoginRequest request = JsonRequestPacketDeserializer::getInstance()->deserializeLoginRequest(req.getBuffer());
	bool result =m_loginManager.login(request.getUsername(), request.getPassword(), sock);
	LoginResponse response(result ? SUCCESS : FAILED);
	buffer buff = JsonResponsePacketSerializer::getInstance()->serializeResponse(response);
	IRequestHandler* handler = nullptr;
	if (result)
	{
		handler = m_handlerFactory.createMenuRequestHandler(m_loginManager.getUser(request.getUsername()));
	}
	return RequestResult(buff, handler);
}

RequestResult LoginRequestHandler::signup(Request req, SOCKET sock)
{
	SignupRequest request = JsonRequestPacketDeserializer::getInstance()->deserializeSignupRequest(req.getBuffer());
	std::regex reg(string(EMAIL_REGEX));
	if (std::regex_match(request.getEmail(), reg)) 
	{
		bool result = m_loginManager.signup(request.getUsername(), request.getPassword(), request.getEmail(), sock);
		SignupResponse response(result ? SUCCESS : FAILED);
		buffer buff = JsonResponsePacketSerializer::getInstance()->serializeResponse(response);
		IRequestHandler* handler = nullptr;
		if (result)
		{
			handler = m_handlerFactory.createMenuRequestHandler(m_loginManager.getUser(request.getUsername()));
		}
		return RequestResult(buff, handler);
	}
	else
	{
		ErrorResponse response("Invalid Email Address!");
		buffer buff = JsonResponsePacketSerializer::getInstance()->serializeResponse(response);
		IRequestHandler* handler = nullptr;//Always gonna go back to here
		return RequestResult(buff, handler);
	}
}
