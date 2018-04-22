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

int bufferToInt(buffer buff)
{
	int ret = 0;
	for (int i = 0; i < buff.size(); i++)
	{
		if (buff[i] == 1)
			ret += pow(2, buff.size() - i);
	}
	return ret;
}

std::string  bufferToString(buffer buff)
{
	std::string ret = "";
	char* letter = nullptr;
	buffer chr;
	for (int i = 0; i < buff.size(); i++)
	{
		if (i % (int)BYTE_SIZE == 0)
		{
			sprintf(letter, "%c", bufferToInt(chr));
			ret += letter;
			chr.empty();
		}
		chr.push_back(buff[i]);
	}

	return ret;
}

json readInfo(buffer buff)
{
	buffer length, content;
	for (int count = 0, i = BYTE_SIZE; count < INT_SIZE * BYTE_SIZE; count++, i++)
	{
		length.push_back(buff[i]);
	}
	int len = bufferToInt(length);
	for (int count = 0; count < len * BYTE_SIZE; count++, i++)
	{
		content.push_back(buff[i]);
	}
	std::string info = bufferToString(content);

	return json(info);
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