#pragma once

#include <WinSock2.h>
#include <vector>

#include "Request.h"
#include "consts.hpp"
#include "Pipe.h"
#include "../locked.hpp"

class PipeManager
{
	locked<std::vector<std::reference_wrapper<const Pipe>>> _pipes;
	SOCKET _sock;
	//You shouldn't be able to copy dis dude
	PipeManager(const PipeManager&);
public:

	PipeManager(SOCKET);

	void addPipe(const Pipe&);
	void clearPipes();

	void write(buffer);//Returns true if it was able to send the data	
	Request read();//Returns a request

	buffer readPacket();

};

