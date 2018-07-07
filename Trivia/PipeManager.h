#pragma once

#include <WinSock2.h>
#include <vector>

#include "Request.h"
#include "consts.hpp"
#include "Pipe.h"
#include "../locked.hpp"

class PipeManager
{
	locked<std::vector<Pipe*>> _pipes;
	SOCKET _sock;
	//You shouldn't be able to copy dis dude
	PipeManager(const PipeManager&);
public:

	PipeManager(SOCKET);
	~PipeManager();
	void addPipe(Pipe*);
	void clearPipes();

	void write(buffer);//Returns true if it was able to send the data	
	Request read();//Returns a request

	buffer readPacket();

};

