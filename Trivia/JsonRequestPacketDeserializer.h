#pragma once
#include "consts.hpp"
#include "LoginRequest.h"
#include "SignupRequest.h"
#include "GetPlayersInRoomRequest.h"
#include "JoinRoomRequest.h"
#include "CreateRoomRequest.h"
#include "SendAnswerRequest.h"
#include "../json.hpp"

using json = nlohmann::json;

class JsonRequestPacketDeserializer
{
	static JsonRequestPacketDeserializer* instance;
	static std::string JsonRequestPacketDeserializer::decapsule(buffer buff);
	JsonRequestPacketDeserializer();
	json readInfo(buffer);

public:
	LoginRequest deserializeLoginRequest(buffer);
	SignupRequest deserializeSignupRequest(buffer);
	GetPlayersInRoomRequest deserializeGetPlayersRequest(buffer);
	JoinRoomRequest deserializeJoinRoomRequest(buffer);
	CreateRoomRequest deserializeCreateRoomRequest(buffer);
	SendAnswerRequest deserializeSendAnswerRequest(buffer);
	static JsonRequestPacketDeserializer* getInstance();
};

