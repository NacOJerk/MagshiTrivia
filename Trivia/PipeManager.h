#pragma once

#include <WinSock2.h>
#include <vector>

#include "Request.h"
#include "consts.hpp"
#include "Pipe.h"

class PipeManager
{
	std::vector<std::reference_wrapper<const Pipe>> _pipes;
	
	//You shouldn't be able to copy dis dude
	PipeManager(const PipeManager&);
public:

	PipeManager();

	void addPipe(const Pipe&);

	void write(buffer, const SOCKET&) const;//Returns true if it was able to send the data	
	Request read(const SOCKET&);//Returns a request

};

