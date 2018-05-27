#pragma once

#include <WinSock2.h>
#include <vector>

#include "consts.hpp"
#include "Pipe.h"

class PipeManager
{
	std::vector<std::reference_wrapper<const Pipe>> _pipes;
	
	//You shouldn't be able to copy dis dude
	PipeManager(const PipeManager&);
public:

	void addPipe(const Pipe&);

	void write(buffer, const SOCKET&) const;//Returns true if it was able to send the data	
	buffer read(const SOCKET&, const unsigned int&);//Returns the readed buffer

	//Based on the functions above
	byte* readBytes(const SOCKET&, const unsigned int&);

};

