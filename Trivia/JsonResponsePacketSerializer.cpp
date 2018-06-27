#include "JsonResponsePacketSerializer.h"
#include "../json.hpp"

using json = nlohmann::json;


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
	string error = "{\"error\": \"" + err.getMessage() + "\"}";
	return encapsule(error, (byte)ERROR_RESPONSE);
}

buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse log)
{
	string res = "{\"status\": \"" + std::to_string(log.getStatus()) + "\"}";
	return encapsule(res, (byte)LOGIN_RESPONSE);
}

buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse sign)
{
	string res = "{\"status\": \"" + std::to_string(sign.getStatus()) + "\"}";
	return encapsule(res, (byte)SIGNUP_RESPONSE);
}

buffer JsonResponsePacketSerializer::serializeResponse(LogoutResponse out)
{
	string res = "{\"status\": \"" + std::to_string(out.getStatus()) + "\"}";
	return encapsule(res, (byte)LOGOUT_RESPONSE);
}

buffer JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse get)
{
	json jsn;
	vector<json> vec;
	vector<Room> rooms = get.getRooms();
	for (auto room : rooms)
	{
		if (room.getData().getIsActive())
			continue;
		json j;
		auto data = room.getData();
		j["admin"] = room.getAllUsers()[0].get().getUsername();
		j["questionTime"] = data.getTimePerQuestion();
		j["maxPlayers"] = data.getMaxPlayers();
		j["numPlayers"] = room.getAllUsers().size();
		j["id"] = data.getId();

		vec.push_back(j);
	}
	jsn["status"] = std::to_string(get.getStatus());
	jsn["rooms"] = vec;

	return encapsule(jsn.dump(), GET_ROOMS_RESPONSE);
}

buffer JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse player)
{
	json jsn;

	jsn["players"] = player.getPlayers();

	return encapsule(jsn.dump(), GET_PLAYERS_IN_ROOM_RESPONSE);
}

buffer JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse res)
{
	json jsn;
	jsn["status"] = res.getStatus();
	return encapsule(jsn.dump(), JOIN_ROOM_RESPONSE);;
}

buffer JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse res)
{
	json jsn;
	jsn["status"] = res.getStatus();
	return encapsule(jsn.dump(), CREATE_ROOM_RESPONSE);;
}

buffer JsonResponsePacketSerializer::serializeResponse(HighscoreResponse res)
{
	
	json jsn;
	vector<json> users;
	vector<Highscore> scores = res.getHighscores();
	for (auto score : scores)
	{
		json j;
		j["name"] = score.getUsername();
		j["score"] = score.getScore();
		users.push_back(j);
	}
	jsn["status"] = res.getStatus();
	jsn["scores"] = users;
	return encapsule(jsn.dump(), HIGHSCORE_RESPONSE);;
}

buffer JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse res)
{
	json jsn;
	jsn["status"] = res.getStatus();

	return encapsule(jsn.dump(), CLOSE_ROOM_RESPONSE);
}

buffer JsonResponsePacketSerializer::serializeResponse(StartGameResponse res)
{
	json jsn;
	jsn["status"] = res.getStatus();

	return encapsule(jsn.dump(), START_GAME_RESPONSE);
}

buffer JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse res)
{
	json jsn;
	jsn["status"] = res.getStatus();
	jsn["has_game_begun"] = res.getHasGameBegun();
	jsn["players"] = res.getPlayers();
	jsn["question_count"] = res.getQuestionCount();
	jsn["answer_timeout"] = res.getAnswerTimeout();

	return encapsule(jsn.dump(), GET_ROOM_STATE_RESPONSE);
}

buffer JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse res)
{
	json jsn;
	jsn["status"] = res.getStatus();

	return encapsule(jsn.dump(), LEAVE_ROOM_RESPONSE);
}

buffer JsonResponsePacketSerializer::serializeResponse(GetStatsResponse res)
{
	json jsn;
	jsn["winRate"] = res.getWinRate();
	jsn["successRate"] = res.getSuccessRate();
	jsn["stupidityRate"] = res.getStuipidityRate();
	jsn["averageTime"] = res.getAverageTime();
	return encapsule(jsn.dump(), STATS_RESPONSE);;
}

buffer JsonResponsePacketSerializer::serializeResponse(SendQuestionResponse res)
{
	json jsn;
	jsn["question"] = res.getQuestion();
	jsn["answers"] = res.getAnswers();
	jsn["remaining"] = res.getRemainingQuestions();
	return encapsule(jsn.dump(), SEND_QUESTION_RESPONSE);;
}

buffer JsonResponsePacketSerializer::serializeResponse(SendAnswerResponse res)
{
	json jsn;
	jsn["status"] = res.getStatus();
	return encapsule(jsn.dump(), SEND_ANSWER_RESPONSE);;
}

buffer JsonResponsePacketSerializer::serializeResponse(SendResultsResponse res)
{
	json jsn;
	jsn["position"] = res.getPosition();
	vector<PlayerResult> pResults = res.getResults();
	vector<json> results;
	for (auto res : pResults)
	{
		json j;
		j["username"] = res.username;
		j["currectAnswer"] = res.currectAnswers;
		j["wrongAnswer"] = res.wrongAnswers;
		j["averageTime"] = res.averageTime;
		results.push_back(j);
	}
	jsn["results"] = results;
	return encapsule(jsn.dump(), SEND_RESULTS_RESPONSE);;
}
