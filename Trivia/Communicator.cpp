#include "consts.hpp"
#include "Communicator.h"
#include "Request.h"
#include "JsonResponsePacketSerializer.h"
#include "ErrorResponse.h"
#include "EncryptionPipe.h"
#include <ctime>

Communicator::Communicator(RequestHandlerFactory & facto, std::pair<Key, Key> keys) : m_handlerFactory(facto), _keys(keys)
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

void Communicator::startEncryption(Client& c)
{
	PipeManager& pipe = c.getPipeManager();

	//Lets sort our keys
	Key publicKey = _keys.first;
	Key privateKey = _keys.second;
	//So the first thing we gonna want to do is to send the public key
	buffer buff = publicKey.getBuffer();
	pipe.write(buff);



	//Next up we want to switch to our encryption pipe
	Pipe* firstPipe = new EncryptionPipe(privateKey);
	pipe.addPipe(firstPipe);

	//Now we gonna get the key from the client
	buff = pipe.readPacket();

	//We gonna consturct it
	privateKey = Key(buff);
	//And we are going to switch to a brand new pipe
	pipe.clearPipes();
	Pipe* secondPipe = new EncryptionPipe(privateKey);
	pipe.addPipe(secondPipe);

	//And we are done :)
}

void Communicator::startThreadForNewClient(SOCKET client_socket)
{
	Client client(client_socket, m_handlerFactory.createLoginRequestHandler());
	try
	{
		startEncryption(client);
	}
	catch (std::exception& e)
	{
		return;
	}
	printf("Client joined\n");

	while (true)
	{
		try
		{
			locked_container<IRequestHandler*> handl = client.getHandler();
			IRequestHandler*& handler = handl;
			Request req = client.getPipeManager().read();
			if (!(handler)->isRequestRelevant(req))
			{
				buffer response = JsonResponsePacketSerializer::getInstance()->serializeResponse(ErrorResponse("Your request does not fit the current state"));
				client.getPipeManager().write(response);
				continue;
			}
			RequestResult result = (handler)->handlRequest(req, client);
			client.getPipeManager().write(result.getBuffer());
			if (result.getNewHandler() != nullptr)
			{
				delete handler;
				handler = result.getNewHandler();
			}
		}
		catch (std::exception& e)
		{
			printf("Client disconnected");
			if (client.isLoggedIn())
				printf(" (%s)", client.getUser().getUsername().c_str());
			printf("\n");
			break;
		}
	}
	if (client.isLoggedIn())
	{
		UserRoomData& roomData = client.getUser().getRoomData();
		if (roomData.loggedIn)
		{
			unsigned int id = roomData.id;
			Room& room = m_handlerFactory.getRoomManager()->getRoom(id);
			if (roomData.isAdmin)
			{
				buffer buff = JsonResponsePacketSerializer::getInstance()->serializeResponse(LeaveRoomResponse(SUCCESS));
				for (auto usr : room.getAllUsers())
				{
					LoggedUser& user = usr.get();
					SOCKET sock = user.getClient().getSocket();
					try 
					{
						client.getPipeManager().write(buff);
					}
					catch (std::exception e)
					{
						//probably user logged out
					}
					if (!user.getRoomData().isAdmin)
					{
						locked<IRequestHandler*>& hand = client.getHandler();
						IRequestHandler** handler = hand;
						delete *handler;
						*handler = m_handlerFactory.createMenuRequestHandler(user);
						hand();
					}
				}
				m_handlerFactory.getRoomManager()->deleteRoom(id);
			}
			else
			{
				room.removeUser(client.getUser().getUsername());
			}
		}
		if (roomData.game)
		{
			m_handlerFactory.getGameManager()->getGame(roomData.game)->removePlayer(client.getUser());
			//Add stuff
		}
		m_handlerFactory.getLoginManager()->logout(client.getUser().getUsername());
	}
}