#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase & data) : m_loginManager(data), _database(data), m_highscoreTable(data)
{

}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(m_loginManager, *this);
}

MenuRequestHandler * RequestHandlerFactory::createMenuRequestHandler(LoggedUser usr)
{
	return new MenuRequestHandler(usr, m_roomManager, m_highscoreTable, m_loginManager,*this);
}

LoginManager * RequestHandlerFactory::getLoginManager()
{
	return &m_loginManager;
}

RoomManager * RequestHandlerFactory::getRoomManager()
{
	return &m_roomManager;
}

HighscoreTable * RequestHandlerFactory::getHighscoreTable()
{
	return &m_highscoreTable;
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser& usr, Room& rm)
{
	return new RoomAdminRequestHandler(rm, usr, m_roomManager, *this);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser& usr, Room& rm)
{
	return new RoomMemberRequestHandler(rm, usr, m_roomManager, *this);
}