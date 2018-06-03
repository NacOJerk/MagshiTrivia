#include "consts.hpp"
#include "Communicator.h"
#include "Request.h"
#include "JsonResponsePacketSerializer.h"
#include "ErrorResponse.h"
#include <ctime>

Communicator::Communicator(RequestHandlerFactory & facto) : m_handlerFactory(facto)
{
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception("Communicator - socket");
}

void Communicator::start(unsigned int port)
{
	bindAndListen(port);
	std::thread(&Communicator::handleRequests, this).detach();
}

void Communicator::bindAndListen(unsigned int port)
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

										// again stepping out to the global namespace
										// Connects between the socket and the configuration (port and etc..)
	if (::bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
}

void Communicator::handleRequests()
{
	while (true)
	{
		SOCKET client_socket = ::accept(_serverSocket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);
		std::thread(&Communicator::startThreadForNewClient ,this , client_socket).detach();
	}
}

void Communicator::sendBuffer(SOCKET socket, buffer buff)
{
	_pm.write(buff, socket);
}



void Communicator::startThreadForNewClient(SOCKET client_socket)
{
	printf("Client joined\n");
	Client client(client_socket, m_handlerFactory.createLoginRequestHandler());
	while (true)
	{
		locked<IRequestHandler*>& hand = client.getHandler();
		IRequestHandler** handler = hand;
		try
		{
			Request req = _pm.read(client_socket);
			if (!(*handler)->isRequestRelevant(req))
			{
				buffer response = JsonResponsePacketSerializer::getInstance()->serializeResponse(ErrorResponse("Your request does not fit the current state"));
				sendBuffer(client_socket, response);
				handler == nullptr;
				hand();
				continue;
			}
			RequestResult result = (*handler)->handlRequest(req, client);
			sendBuffer(client_socket, result.getBuffer());
			if (result.getNewHandler() != nullptr)
			{
				delete *handler;
				*handler = result.getNewHandler();
			}
			handler == nullptr;
			hand();
		}
		catch (std::exception& e)
		{
			if (handler)
				hand();
			printf("Client disconnected");
			if (client.isLoggedIn())
				printf(" (%s)", client.getUser().getUsername().c_str());
			printf("\n");
			break;
		}
	}
	if (client.isLoggedIn())
		m_handlerFactory.getLoginManager()->logout(client.getUser().getUsername());
}