#include "RoomMemberRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "LeaveRoomResponse.h"
#include "GetRoomStateResponse.h"
#include "consts.hpp"

RoomMemberRequestHandler::RoomMemberRequestHandler(Room& room, LoggedUser& user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : m_room(room), m_user(user), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{}

bool RoomMemberRequestHandler::isRequestRelevant(Request request)
{
	RequestId id = request.getID();
	return id == LEAVE_ROOM_REQUEST || id == GET_ROOM_STATE_REQUEST;
}

RequestResult RoomMemberRequestHandler::handlRequest(Request request, Client& c)
{
	RequestId id = request.getID();

	switch (id)
	{
	case GET_ROOM_STATE_REQUEST:
		return getRoomState(request);
	case LEAVE_ROOM_REQUEST:
		return leaveRoom(request);
	}
	throw std::exception("Couldn't handle packet");
}

RequestResult RoomMemberRequestHandler::getRoomState(Request request)
{
	unsigned int status = SUCCESS, questionCount = m_room.getData().getAmountQuestions(), answerTimeout = m_room.getData().getTimePerQuestion();
	vector<string> players;
	bool hasGameBegun = m_room.getData().getIsActive();
	auto& users = m_room.getAllUsers();
	printf("Amount of users %d\n", users.size());
	for (auto user : users)
	{
		players.push_back(user.get().getUsername());
	}
	printf("Amount of names %d\n");
	GetRoomStateResponse res(status, hasGameBegun, players, questionCount, answerTimeout, m_room.getData().getMaxPlayers());
	buffer buff = JsonResponsePacketSerializer::getInstance()->serializeResponse(res);

	return RequestResult(buff, nullptr);
}

RequestResult RoomMemberRequestHandler::leaveRoom(Request request)
{
	m_room.removeUser(m_user.getUsername());
	LeaveRoomResponse res(SUCCESS);
	buffer buff = JsonResponsePacketSerializer::getInstance()->serializeResponse(res);
	IRequestHandler* handler = m_handlerFactory.createMenuRequestHandler(m_user);
	return RequestResult(buff, handler);
}