#pragma once
#include <vector>
#include <algorithm>

#define SUCCESS 1
#define FAILED 0

enum RequestId { LOGIN_REQUEST = 1, SIGNUP_REQUEST,FINAL_ENUM };
enum ResponseId { ERROR_RESPONSE = FINAL_ENUM, SIGNUP_RESPONSE, LOGIN_RESPONSE};
typedef unsigned char byte;
typedef std::vector<byte> buffer;

static RequestId getEnumFromID(byte id)
{
	return static_cast<RequestId>(id);
}