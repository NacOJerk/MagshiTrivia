#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RoomAdminRequestHandler : public IRequestHandler
{
private:
	Room& m_room;
	LoggedUser& m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult LeaveRoom(Request);
	RequestResult getRoomState(Request);

public:
	RoomAdminRequestHandler(Room&, LoggedUser&, RoomManager&, RequestHandlerFactory&);

	bool isRequestRelevant(Request);
	RequestResult handleRequest(Request);
};