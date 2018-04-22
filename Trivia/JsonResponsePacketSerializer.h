#pragma once
#include "consts.h"
#include "ErrorResponse.h"
#include "LoginResponse.h"
#include "SignupResponse.h"
#include "LogoutResponse.h"
#include "GetRoomsResponse.h"
#include "GetPlayersInRoomResponse.h"
#include "JoinRoomResponse.h"
#include "CreateRoomResponse.h"
#include "HighscoreResponse.h"

class JsonResponsePacketSerializer
{
	static JsonResponsePacketSerializer* instance;
	static buffer encapsule(std::string text, byte id);
	JsonResponsePacketSerializer();
public:
	buffer serializeResponse(ErrorResponse);
	buffer serializeResponse(LoginResponse);
	buffer serializeResponse(SignupResponse);
	buffer serializeResponse(LogoutResponse);
	buffer serializeResponse(GetRoomsResponse);
	buffer serializeResponse(GetPlayersInRoomResponse);
	buffer serializeResponse(JoinRoomResponse);
	buffer serializeResponse(CreateRoomResponse);
	buffer serializeResponse(HighscoreResponse);
	static JsonResponsePacketSerializer* getInstance();
};

