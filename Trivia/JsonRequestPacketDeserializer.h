#pragma once
#include "consts.h"
#include "LoginRequest.h"
#include "SignupRequest.h"
#include "GetPlayersInRoomRequest.h"
#include "JoinRoomRequest.h"
#include "CreateRoomRequest.h"

class JsonRequestPacketDeserializer
{
	static JsonRequestPacketDeserializer* instance;
	static std::string JsonRequestPacketDeserializer::decapsule(buffer buff);
	JsonRequestPacketDeserializer();

public:
	LoginRequest deserializeLoginRequest(buffer);
	SignupRequest deserializeSignupRequest(buffer);
	GetPlayersInRoomRequest deserializeGetPlayersRequest(buffer);
	JoinRoomRequest deserializeJoinRoomRequest(buffer);
	CreateRoomRequest deserializeCreateRoomRequest(buffer);
	static JsonRequestPacketDeserializer* getInstance();
};

