#include "MenuRequestHandler.h"
#include "LogoutResponse.h"
#include "CreateRoomRequest.h"
#include "CreateRoomResponse.h"
#include "JoinRoomResponse.h"
#include "JoinRoomRequest.h"
#include "GetRoomsResponse.h"
#include "GetPlayersInRoomRequest.h"
#include "GetPlayersInRoomResponse.h"
#include "GetStatsResponse.h"
#include "HighscoreResponse.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

RequestResult MenuRequestHandler::signout(Request)
{
	m_loginManager.logout(m_users.getUsername());
	unsigned int status = SUCCESS;
	return RequestResult(JsonResponsePacketSerializer::getInstance()->serializeResponse(LogoutResponse(status)), m_handlerFactory.createLoginRequestHandler());
}

RequestResult MenuRequestHandler::getRooms(Request)
{
	unsigned int status = SUCCESS;
	return RequestResult(JsonResponsePacketSerializer::getInstance()->serializeResponse(GetRoomsResponse(status, m_roomManager.getRooms())),(IRequestHandler*) nullptr);
}

RequestResult MenuRequestHandler::getPlayersInRoom(Request r)
{
	GetPlayersInRoomRequest req = JsonRequestPacketDeserializer::getInstance()->deserializeGetPlayersRequest(r.getBuffer());
	if (m_roomManager.hasRoom(req.getRoomId()))
	{
		return RequestResult(JsonResponsePacketSerializer::getInstance()->serializeResponse(ErrorResponse("The room doesn't exists")), nullptr);
	}
	vector<std::reference_wrapper<LoggedUser>>& lUsers = m_roomManager.getRoom(req.getRoomId()).getAllUsers();
	vector<string> users;
	for (auto user : lUsers)
	{
		users.push_back(user.get().getUsername());
	}
	return RequestResult(JsonResponsePacketSerializer::getInstance()->serializeResponse(GetPlayersInRoomResponse(users)), nullptr);
}

RequestResult MenuRequestHandler::getHighscores(Request)
{
	unsigned int status = SUCCESS;
	vector<Highscore> scores = m_highscoreTable.getHighscores();
	return RequestResult(JsonResponsePacketSerializer::getInstance()->serializeResponse(HighscoreResponse(status, scores)), nullptr);
}

RequestResult MenuRequestHandler::joinRoom(Request r)
{
	JoinRoomRequest req = JsonRequestPacketDeserializer::getInstance()->deserializeJoinRoomRequest(r.getBuffer());
	unsigned int status = m_roomManager.hasRoom(req.getRoomId()) ? SUCCESS : FAILED;
	IRequestHandler* handler = nullptr;
	if (status == SUCCESS)
	{
		printf("Max users %d\n", m_roomManager.getRoom(req.getRoomId()).getData().getMaxPlayers());
		printf("Current amout of users %d\n", m_roomManager.getRoom(req.getRoomId()).getAllUsers().size());
		if (m_roomManager.getRoom(req.getRoomId()).getData().getMaxPlayers() <= m_roomManager.getRoom(req.getRoomId()).getAllUsers().size())
		{
			status = FAILED;
		}
		else
		{
			m_roomManager.getRoom(req.getRoomId()).addUser(m_users);
			handler = m_handlerFactory.createRoomMemberRequestHandler(m_users, m_roomManager.getRoom(req.getRoomId()));
		}
	}
	return RequestResult(JsonResponsePacketSerializer::getInstance()->serializeResponse(JoinRoomResponse(status)), handler);
}

RequestResult MenuRequestHandler::createRoom(Request r)
{
	CreateRoomRequest req = JsonRequestPacketDeserializer::getInstance()->deserializeCreateRoomRequest(r.getBuffer());

	unsigned int status = !(req.getMaxUsers() < 1 || req.getAnswerTimeout() < 1 || req.getQuestionCount() < 1 || m_handlerFactory.getDatabase().getQuestions(req.getQuestionCount()).size() < req.getQuestionCount()) ? SUCCESS : FAILED;
	IRequestHandler* handler = nullptr;

	if (status == SUCCESS)
	{
		status = m_roomManager.createRoom(m_users, req.getMaxUsers(), req.getAnswerTimeout(), req.getQuestionCount());
		handler = m_handlerFactory.createRoomAdminRequestHandler(m_users, m_roomManager.getRoom(status));
	}
	return RequestResult(JsonResponsePacketSerializer::getInstance()->serializeResponse(CreateRoomResponse(status)), handler);
}

RequestResult MenuRequestHandler::getStats(Request r)
{
	const std::string username = m_users.getUsername();
	float winRate = m_highscoreTable.getWinRate(username);
	float successRate = m_highscoreTable.getSuccessRate(username);
	float stuipidityRate = m_highscoreTable.getStuipdityRate(username);
	float averageTime = m_highscoreTable.getAverageTime(username);
	return RequestResult(JsonResponsePacketSerializer::getInstance()->serializeResponse(GetStatsResponse(winRate,successRate,stuipidityRate,averageTime)), nullptr);
}



MenuRequestHandler::MenuRequestHandler(LoggedUser& usr, RoomManager & rm, HighscoreTable & ht, LoginManager & lm, RequestHandlerFactory & rhf) : m_users(usr), m_roomManager(rm), m_highscoreTable(ht), m_loginManager(lm), m_handlerFactory(rhf)
{

}

bool MenuRequestHandler::isRequestRelevant(Request req)
{
	RequestId id = req.getID();
	return id == GET_PLAYERS_IN_ROOM_REQUEST || id == JOIN_ROOM_REQUEST || id == CREATE_ROOM_REQUEST || id == SIGNOUT_REQUEST || id == GET_ROOMS_REQUEST || id == GET_HIGHSCORE || id == GET_STATS_REQUEST;
}

RequestResult MenuRequestHandler::handlRequest(Request req, Client& sock)
{
	switch (req.getID())
	{
	case GET_PLAYERS_IN_ROOM_REQUEST:
		return getPlayersInRoom(req);
	case JOIN_ROOM_REQUEST:
		return joinRoom(req);
	case CREATE_ROOM_REQUEST:
		return createRoom(req);
	case SIGNOUT_REQUEST:
		return signout(req);
	case GET_ROOMS_REQUEST:
		return getRooms(req);
	case GET_HIGHSCORE:
		return getHighscores(req);
	case GET_STATS_REQUEST:
		return getStats(req);
	}
	throw std::exception("Couldn't handle packet");
}

