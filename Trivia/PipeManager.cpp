#include "PipeManager.h"

PipeManager::PipeManager(SOCKET sock) : _sock(sock)
{
}

PipeManager::~PipeManager()
{
	locked_container<std::vector<Pipe*>> pipes = _pipes;
	std::vector<Pipe*>& _pipes = pipes;
	for (auto p : _pipes)
	{
		if (p)
			delete p;
	}
}

void PipeManager::addPipe(Pipe*  pipe)
{
	locked_container<std::vector<Pipe*>> pipes = _pipes;
	std::vector<Pipe*>& _pipes = pipes;
	_pipes.push_back(pipe);
}

void PipeManager::clearPipes()
{
	locked_container<std::vector<Pipe*>> pipes = _pipes;
	std::vector<Pipe*>& _pipes = pipes;
	for (auto p : _pipes)
	{
		if (p)
			delete p;
	}
	_pipes.clear();
}

void writ(SOCKET socket, char * data, unsigned int length)
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



void PipeManager::write(buffer buf)
{
	{
		locked_container<std::vector<Pipe*>> pipes = _pipes;
		std::vector<Pipe*>& _pipes = pipes;
		//Piping it up
		for (auto pipe : _pipes)
		{
			buf = pipe->write(buf);
		}
	}
	//Set up for like ya know sending the stuff
	union byteint
	{
		byte b[4];
		unsigned int ia;
	};

	byteint length;
	length.ia = buf.size();
	char* data = new char[buf.size() + 4];

	for (int i = 0; i < 4; data[i] = length.b[3 - i], i++);
	for (unsigned int i = 0; i < buf.size(); data[i + 4] = buf[i], i++);

	writ(_sock, data, buf.size() + 4);
}

char* recive(const SOCKET& socket, const unsigned int& length)
{
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
	return chars;
}

Request PipeManager::read()
{
	buffer buf = readPacket();

	byte id = buf[0];
	unsigned int length = buf[1] << 24 | buf[2] << 16 | buf[3] << 8 | buf[4];
	buf.erase(buf.begin(), buf.begin() + 5);

	if (length != buf.size())
		throw std::exception("Buffer size and length size mismatch");

	return Request(getEnumFromID(id), time(0), buf);
}

buffer PipeManager::readPacket()
{
	unsigned char* len = (unsigned char*)recive(_sock, 4);
	unsigned int length = len[0] << 24 | len[1] << 16 | len[2] << 8 | len[3];
	delete len;

	char* chars = recive(_sock, length);
	//First I recive them bytes

	//moving the things to buff
	buffer buf;
	for (unsigned int i = 0; i < length; buf.push_back(chars[i++]));
	delete chars;

	{
		locked_container<std::vector<Pipe*>> pipes = _pipes;
		std::vector<Pipe*>& _pipes = pipes;//Using the pipes for the least amount of time
		//piping the things
		for (auto rit = _pipes.rbegin(); rit != _pipes.rend(); ++rit)
			buf = (*rit)->read(buf);
	}
	return buf;
}
