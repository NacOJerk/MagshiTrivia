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

byte * Communicator::readBytes(SOCKET socket, unsigned int length)
{
	char* chars = new char[length];
	int pos = 0;
	do
	{
		int result = recv(socket, chars + pos, length, 0);
		pos += result;
		if (result == INVALID_SOCKET)
		{
			delete chars;
			throw std::exception("Error while reciving data from socket");
		}
	} while (pos < length);
	return (byte*)chars;
}

void Communicator::sendDataToSocket(SOCKET socket, char * data, unsigned int length)
{
	int pos = 0;
	do
	{
		int result = send(socket, data + pos, length, 0);
		if (result == INVALID_SOCKET)
		{
			throw std::exception("Error while sending data to socket");
		}
		pos += result;
	} while (pos < length);
}

byte Communicator::getId(SOCKET socket)
{
	byte* idc = readBytes(socket, 1);
	byte id = *idc;
	delete idc;
	return id;
}

unsigned int Communicator::getLength(SOCKET socket)
{
	byte* lengthC = readBytes(socket, 4);
	unsigned int length = lengthC[0] << 24 | lengthC[1] << 16 | lengthC[2] << 8 | lengthC[3];
	delete lengthC;
	return length;
}

buffer Communicator::getBuffer(SOCKET socket, unsigned int length)
{
	byte* buffC = readBytes(socket, length);
	buffer buff;
	for (int i = 0; i < length; buff.push_back(buffC[i++]));
	delete buffC;
	return buff;
}

void Communicator::sendBuffer(SOCKET socket, buffer buff)
{
	char* data = new char[buff.size()];
	for (int i = 0; i < buff.size();data[i] = buff[i], i++);
	int result =  send(socket, data, buff.size(), 0);
	delete data;
	if (result == INVALID_SOCKET)
	{
		throw std::exception("Error while sending data to socket");
	}
}



void Communicator::startThreadForNewClient(SOCKET client_socket)
{
	IRequestHandler* handler = m_handlerFactory.createLoginRequestHandler();
	while (true)
	{
		byte id = getId(client_socket);
		buffer buff = getBuffer(client_socket, getLength(client_socket));
		Request req(getEnumFromID(id), time(0), buff);
		if (!handler->isRequestRelevant(req))
		{
			buffer response = JsonResponsePacketSerializer::getInstance()->serializeResponse(ErrorResponse("Your request does not fit the current state"));
			sendBuffer(client_socket, response);
			continue;
		}
		RequestResult result = handler->handlRequest(req);
		sendBuffer(client_socket, result.getBuffer());
		if (result.getNewHandler() != nullptr)
		{
			delete handler;
			handler = result.getNewHandler();
		}
	}
	if (handler)
		delete handler;
}
