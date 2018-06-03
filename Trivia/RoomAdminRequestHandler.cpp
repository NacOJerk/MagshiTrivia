#include "RoomAdminRequestHandler.h"
#include "CloseRoomResponse.h"
#include "StartGameResponse.h"
#include "GetRoomStateResponse.h"
#include "JsonResponsePacketSerializer.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room& room, LoggedUser& user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : m_room(room), m_user(user), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{}

bool RoomAdminRequestHandler::isRequestRelevant(Request request)
{
	RequestId id = request.getID();
	return id == GET_ROOM_STATE_REQUEST || id == CLOSE_ROOM_REQUEST || id == START_GAME_REQUEST;
}

RequestResult RoomAdminRequestHandler::handleRequest(Request request)
{
	RequestId id = request.getID();

	switch (id)
	{
	case GET_ROOM_STATE_REQUEST:
		return getRoomState(request);
	case CLOSE_ROOM_REQUEST:
		return closeRoom(request);
	case START_GAME_REQUEST:
		return startGame(request);
	}
	throw std::exception("Couldn't handle packet");
}

RequestResult RoomAdminRequestHandler::closeRoom(Request request)
{
	vector<std::reference_wrapper<LoggedUser>>& users = m_room.getAllUsers();
	while (!users.empty())
	{
		string name = users[0].get().getUsername();
		m_room.removeUser(name);
	}
	unsigned int id = m_room.getData().getId();
	m_roomManager.deleteRoom(id);
	CloseRoomResponse res(SUCCESS);
	buffer buff = JsonResponsePacketSerializer::getInstance()->serializeResponse(res);
	IRequestHandler* handler = nullptr;
	handler = m_handlerFactory.createMenuRequestHandler(m_user);

	return RequestResult(buff, handler);
}

RequestResult RoomAdminRequestHandler::getRoomState(Request request)
{
	unsigned int status = SUCCESS, questionCount = m_room.getData().getAmountQuestions(), answerTimeout = m_room.getData().getTimePerQuestion();
	vector<string> players;
	bool hasGameBegun = m_room.getData().getIsActive();
	auto& users = m_room.getAllUsers();
	for (auto user : users)
	{
		players.push_back(user.get().getUsername());
	}
	GetRoomStateResponse res(status, hasGameBegun, players, questionCount, answerTimeout);
	buffer buff = JsonResponsePacketSerializer::getInstance()->serializeResponse(res);

	return RequestResult(buff, nullptr);
}

RequestResult RoomAdminRequestHandler::startGame(Request request)
{
	StartGameResponse res(SUCCESS);
	buffer buff = JsonResponsePacketSerializer::getInstance()->serializeResponse(res);

	return RequestResult(buff, nullptr);
}