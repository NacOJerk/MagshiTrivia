#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
private:
	Room& m_room;
	LoggedUser& m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult closeRoom(Request);
	RequestResult startGame(Request);
	RequestResult getRoomState(Request);

public:
	RoomAdminRequestHandler(Room&, LoggedUser&, RoomManager&, RequestHandlerFactory&);

	bool isRequestRelevant(Request) override;
	RequestResult handlRequest(Request, Client&) override;
};