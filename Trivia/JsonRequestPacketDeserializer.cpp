#include "JsonRequestPacketDeserializer.h"
#include "../json.hpp"
#include <cmath>

#define BYTE_SIZE 8.0
#define INT_SIZE 4.0

using json = nlohmann::json;

JsonRequestPacketDeserializer* JsonRequestPacketDeserializer::instance = 0;

std::string JsonRequestPacketDeserializer::decapsule(buffer buff)
{
	std::string str;
	for (int i = 0; i < buff.size(); str += buff[i++]);
	return str;
}

json JsonRequestPacketDeserializer::readInfo(buffer buff)
{
	return json::parse(decapsule(buff));
}

JsonRequestPacketDeserializer::JsonRequestPacketDeserializer()
{
}

JsonRequestPacketDeserializer * JsonRequestPacketDeserializer::getInstance()
{
	if (!instance)
		instance = new JsonRequestPacketDeserializer();
	return instance;
}

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(buffer buff)
{
	json j_info = readInfo(buff);

	return LoginRequest(j_info["username"], j_info["password"]);
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(buffer buff)
{
	json j_info = readInfo(buff);

	return SignupRequest(j_info["username"], j_info["password"], j_info["email"]);
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(buffer buff)
{
	json j_info = readInfo(buff);

	return GetPlayersInRoomRequest(j_info["id"]);
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(buffer buff)
{
	json j_info = readInfo(buff);

	return JoinRoomRequest(j_info["id"]);
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(buffer buff)
{
	json j_info = readInfo(buff);

	return CreateRoomRequest(j_info["username"], j_info["maxUsers"], j_info["questionCount"], j_info["answerTimeout"]);
}