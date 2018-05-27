#include "PipeManager.h"

void PipeManager::addPipe(const Pipe & pipe)
{
	_pipes.push_back(pipe);
}

void PipeManager::write(buffer buf, const SOCKET & socket) const
{
	//Piping it up
	for (auto pipe : _pipes)
	{
		buf = pipe.get().write(buf);
	}

	//Set up for like ya know sending the stuff
	char* data = new char[buf.size()];
	const unsigned int length = buf.size();
	for (unsigned int i = 0; i < length, data[i] = buf[i++]);
	
	//Sending the thingy
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

buffer PipeManager::read(const SOCKET & socket, const unsigned int & length)
{
	//First I recive them bytes
	char* chars = new char[length];
	int pos = 0;
	do
	{
		int result = recv(socket, chars + pos, length, 0);
		pos += result;
		if (result == INVALID_SOCKET || result == 0)
		{
			delete chars;
			throw std::exception("Error while reciving data from socket");
		}
	} while (pos < length);

	//moving the things to buff
	buffer buf;
	for (unsigned int i = 0; i < length; buf.push_back(chars[i++]));
	delete chars;

	//piping the things
	for (auto pipe : _pipes)
		buf = pipe.get().read(buf);

	return buf;
}

byte * PipeManager::readBytes(const SOCKET & socket, const unsigned int & length)
{
	buffer buf = read(socket, length);
	byte* data = new byte[buf.size()];
	return nullptr;
}
