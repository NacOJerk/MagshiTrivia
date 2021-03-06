#pragma once
#include <vector>
#include <algorithm>

#define SUCCESS 1
#define FAILED 0

enum RequestId { LOGIN_REQUEST = 1, SIGNUP_REQUEST,   GET_PLAYERS_IN_ROOM_REQUEST, JOIN_ROOM_REQUEST, CREATE_ROOM_REQUEST, SIGNOUT_REQUEST, GET_ROOMS_REQUEST, GET_HIGHSCORE, CLOSE_ROOM_REQUEST, START_GAME_REQUEST, GET_ROOM_STATE_REQUEST, LEAVE_ROOM_REQUEST, SEND_ANSWER_REQUEST, GET_STATS_REQUEST };
enum ResponseId { ERROR_RESPONSE = 100, SIGNUP_RESPONSE, LOGIN_RESPONSE, CREATE_ROOM_RESPONSE, GET_PLAYERS_IN_ROOM_RESPONSE, GET_ROOMS_RESPONSE, HIGHSCORE_RESPONSE, JOIN_ROOM_RESPONSE, LOGOUT_RESPONSE, CLOSE_ROOM_RESPONSE, START_GAME_RESPONSE, GET_ROOM_STATE_RESPONSE, LEAVE_ROOM_RESPONSE, SEND_QUESTION_RESPONSE, SEND_ANSWER_RESPONSE, SEND_RESULTS_RESPONSE , STATS_RESPONSE };
enum StupidMeter { GENIUS = 0, CHALLENGED = 20, DUMB = 50, BRICK = 100 };
typedef unsigned char byte;
typedef std::vector<byte> buffer;

static RequestId getEnumFromID(byte id)
{
	return static_cast<RequestId>(id);
}