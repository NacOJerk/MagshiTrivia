#pragma once
#include "consts.h"
#include "ErrorResponse.h"
#include "LoginResponse.h"
#include "SignupResponse.h"

class JsonResponsePacketSerializer
{
	static JsonResponsePacketSerializer* instance;
	static buffer encapsule(std::string text, byte id);
	JsonResponsePacketSerializer();
public:
	buffer serializeResponse(ErrorResponse);
	buffer serializeResponse(LoginResponse);
	buffer serializeResponse(SignupResponse);
	static JsonResponsePacketSerializer* getInstance();
};

