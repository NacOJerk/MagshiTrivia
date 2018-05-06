#include "JsonResponsePacketSerializer.h"


JsonResponsePacketSerializer* JsonResponsePacketSerializer::instance = 0;

union byteint
{
	byte b[4];
	int ia;
};

buffer JsonResponsePacketSerializer::encapsule(std::string text, byte id)
{
	buffer buff;
	buff.push_back(id);
	byteint length{ text.size() };

	for (int i = 0; i < 4; buff.push_back(length.b[3-i++]));
	for (int i = 0; i < length.ia; buff.push_back(text[i++]));
	return buff;
}

JsonResponsePacketSerializer::JsonResponsePacketSerializer()
{
}

JsonResponsePacketSerializer * JsonResponsePacketSerializer::getInstance()
{
	if (!instance)
		instance = new JsonResponsePacketSerializer();
	return instance;
}

buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse err)
{
	return encapsule(err.getMessage(), (byte)ERROR_RESPONSE);
}

buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse log)
{
	return encapsule(std::to_string(log.getStatus()), (byte)LOGIN_RESPONSE);
}

buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse sign)
{
	return encapsule(std::to_string(sign.getStatus()), (byte)SIGNUP_RESPONSE);
}