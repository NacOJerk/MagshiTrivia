#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include <iostream>
#include "Server.h"


void main()
{
	std::cout << "Starting server...." << std::endl;
	try
	{
		WSAInitializer wsaInit;
		Server* myServer = Server::getInstance();

		myServer->run();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");
}