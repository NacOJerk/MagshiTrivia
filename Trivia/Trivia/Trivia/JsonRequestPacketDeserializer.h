#pragma once
#include "consts.h"
#include "LoginRequest.h"
#include "SignupRequest.h"

class JsonRequestPacketDeserializer
{
	static JsonRequestPacketDeserializer* instance;
	static std::string JsonRequestPacketDeserializer::decapsule(buffer buff);
	JsonRequestPacketDeserializer();

public:
	LoginRequest deserializeLoginRequest(buffer);
	SignupRequest deserializeSignupRequest(buffer);
	static JsonRequestPacketDeserializer* getInstance();
};

