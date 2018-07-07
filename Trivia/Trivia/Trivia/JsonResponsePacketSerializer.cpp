#include "JsonResponsePacketSerializer.h"


JsonResponsePacketSerializer* JsonResponsePacketSerializer::instance = 0;

buffer JsonResponsePacketSerializer::encapsule(std::string text, byte id)
{
	buffer buff;
	buff.push_back(id);
	unsigned int length = text.size();
	byte* lengthC = (byte*)&length;
	for (int i = 0; i < 4; buff.push_back(lengthC[i++]));
	for (int i = 0; i < length; buff.push_back(text[i++]));
}


buffer serializeMessage(std::string id, std::string length, std::string content)
{
	std::string serial = id + length + content;
	buffer buff;
	for (char bit : serial)
	{
		buff.push_back(bit - '0');
	}
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
	std::string id = intToBytes(ERROR_RESPONSE, CHAR_SIZE);
	std::string length = intToBytes(err.getMessage().size(), INT_SIZE);
	std::string content = stringToBytes(err.getMessage());
	
	return serializeMessage(id, length, content);
}

buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse log)
{
	std::string id = intToBytes(LOGIN_RESPONSE, CHAR_SIZE);
	std::string length = intToBytes(INT_SIZE, INT_SIZE);
	std::string content = intToBytes(log.getStatus(), INT_SIZE);

	return serializeMessage(id, length, content);
}

buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse sign)
{
	std::string id = intToBytes(SIGNUP_RESPONSE, 1);
	std::string length = intToBytes(INT_SIZE, INT_SIZE);
	std::string content = intToBytes(sign.getStatus(), INT_SIZE);

	return serializeMessage(id, length, content);
}