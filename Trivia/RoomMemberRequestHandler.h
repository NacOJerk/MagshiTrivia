#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RoomMemberRequestHandler : public IRequestHandler
{
private:
	Room& m_room;
	LoggedUser& m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult leaveRoom(Request);
	RequestResult getRoomState(Request);

	RequestResult handlRequest(Request, Client&)
	{
		//unnecessary function
		//preventing overload errors
		return RequestResult(buffer(), nullptr);
	}

public:
	RoomMemberRequestHandler(Room&, LoggedUser&, RoomManager&, RequestHandlerFactory&);

	bool isRequestRelevant(Request);
	RequestResult handleRequest(Request);
};