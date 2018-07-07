#include "Client.h"

Client::Client(SOCKET socket, IRequestHandler* handler) : _socket(socket), _usr(nullptr), _handler(handler), _pm(socket)
{
}

Client::~Client()
{
	IRequestHandler** handler = _handler;
	delete *handler;
	_handler();
}

SOCKET Client::getSocket()
{
	return _socket;
}

locked<IRequestHandler*>& Client::getHandler()
{
	return _handler;
}

void Client::setUser(LoggedUser * usr)
{
	if (_usr && usr)
		throw std::exception("You can not changed the user of the client after it have been set");
	_usr = usr;
}

bool Client::isLoggedIn() const
{
	return _usr;
}

LoggedUser & Client::getUser()
{
	if (!isLoggedIn())
		throw std::exception("You can not get a user until the client is logged in");
	return *_usr;
}

PipeManager & Client::getPipeManager()
{
	return _pm;
}
