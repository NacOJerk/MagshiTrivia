#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "LoginResponse.h"
#include "SignupResponse.h"
#include <exception>
#include <utility>

LoginRequestHandler::LoginRequestHandler(LoginManager & mang, RequestHandlerFactory & facto) : m_loginManager(mang), m_handlerFactory(facto)
{
}

bool LoginRequestHandler::isRequestRelevant(Request request)
{
	RequestId id = request.getID();
	return id == LOGIN_REQUEST || id == SIGNUP_REQUEST;
}

RequestResult LoginRequestHandler::handlRequest(Request request)	
{
	switch (request.getID())
	{
	case LOGIN_REQUEST:
		return login(request);
	case SIGNUP_REQUEST:
		return signup(request);
	}
	throw std::exception("Couldn't handle packet");
}

RequestResult LoginRequestHandler::login(Request req)
{
	LoginRequest request = JsonRequestPacketDeserializer::getInstance()->deserializeLoginRequest(req.getBuffer());
	bool result =m_loginManager.login(request.getUsername(), request.getPassword());
	LoginResponse response(result ? SUCCESS : FAILED);
	buffer buff = JsonResponsePacketSerializer::getInstance()->serializeResponse(response);
	IRequestHandler* handler = nullptr;
	if (result)
	{
		// ADD MENU IN HERE
	}
	return RequestResult(buff, handler);
}

RequestResult LoginRequestHandler::signup(Request req)
{
	SignupRequest request = JsonRequestPacketDeserializer::getInstance()->deserializeSignupRequest(req.getBuffer());
	bool result = m_loginManager.signup(request.getUsername(), request.getPassword(), request.getEmail());
	SignupResponse response(result ? SUCCESS : FAILED);
	buffer buff = JsonResponsePacketSerializer::getInstance()->serializeResponse(response);
	IRequestHandler* handler = nullptr;//Always gonna go back to here
	return RequestResult(buff, handler);
}
