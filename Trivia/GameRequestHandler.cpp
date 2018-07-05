#include "GameRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "SendAnswerResponse.h"
#include "SendAnswerRequest.h"

RequestResult GameRequestHandler::submitAnswer(Request req)
{
	SendAnswerRequest request = JsonRequestPacketDeserializer::getInstance()->deserializeSendAnswerRequest(req.getBuffer());
	m_game.submitAnswer(m_user, request.getAnswer(), req.getRecivalTime());
	return RequestResult(JsonResponsePacketSerializer::getInstance()->serializeResponse(SendAnswerResponse(1)), nullptr);
}

RequestResult GameRequestHandler::leaveGame(Request)
{
	m_game.removePlayer(m_user);
	LeaveRoomResponse res(SUCCESS);
	buffer buff = JsonResponsePacketSerializer::getInstance()->serializeResponse(res);
	IRequestHandler* handler = m_handlerFactory.createMenuRequestHandler(m_user);
	return RequestResult(buff, handler);
}

GameRequestHandler::GameRequestHandler(Game & g , LoggedUser & u , RequestHandlerFactory & f) : m_game(g), m_user(u), m_handlerFactory(f)
{
}

bool GameRequestHandler::isRequestRelevant(Request req)
{
	RequestId id = req.getID();
	return id == SEND_ANSWER_REQUEST || LEAVE_ROOM_REQUEST;
}

RequestResult GameRequestHandler::handlRequest(Request req, Client & c)
{
	switch (req.getID())
	{
	case SEND_ANSWER_REQUEST:
		return submitAnswer(req);
	case LEAVE_ROOM_REQUEST:
		return leaveGame(req);
	}
	throw std::exception("Couldn't handle packet");
}
