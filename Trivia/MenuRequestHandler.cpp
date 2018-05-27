#include "MenuRequestHandler.h"
#include "LogoutResponse.h"
#include "CreateRoomRequest.h"
#include "CreateRoomResponse.h"
#include "JoinRoomResponse.h"
#include "JoinRoomRequest.h"
#include "GetRoomsResponse.h"
#include "GetPlayersInRoomRequest.h"
#include "GetPlayersInRoomResponse.h"
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
	if(status == SUCCESS)
		m_roomManager.getRoom(r.getID()).addUser(m_users);
	return RequestResult(JsonResponsePacketSerializer::getInstance()->serializeResponse(JoinRoomResponse(status)), nullptr);
}

RequestResult MenuRequestHandler::createRoom(Request r)
{
	CreateRoomRequest req = JsonRequestPacketDeserializer::getInstance()->deserializeCreateRoomRequest(r.getBuffer());
	unsigned int status = !(req.getMaxUsers() < 1 || req.getAnswerTimeout() < 1 || req.getQuestionCount() < 1) ? SUCCESS : FAILED;
	if(status == SUCCESS)
		status = m_roomManager.createRoom(m_users, req.getMaxUsers(), req.getAnswerTimeout(), req.getQuestionCount());
	return RequestResult(JsonResponsePacketSerializer::getInstance()->serializeResponse(CreateRoomResponse(status)), nullptr);
}



MenuRequestHandler::MenuRequestHandler(LoggedUser& usr, RoomManager & rm, HighscoreTable & ht, LoginManager & lm, RequestHandlerFactory & rhf) : m_users(usr), m_roomManager(rm), m_highscoreTable(ht), m_loginManager(lm), m_handlerFactory(rhf)
{

}

bool MenuRequestHandler::isRequestRelevant(Request req)
{
	RequestId id = req.getID();
	return id == GET_PLAYERS_IN_ROOM_REQUEST || id == JOIN_ROOM_REQUEST || id == CREATE_ROOM_REQUEST || id == SIGNOUT_REQUEST || id == GET_ROOMS_REQUEST || id == GET_HIGHSCORE;
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
		return signout(req);
	case GET_HIGHSCORE:
		return getHighscores(req);
	}
	throw std::exception("Couldn't handle packet");
}

