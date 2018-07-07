#include "PipeManager.h"

PipeManager::PipeManager(SOCKET sock) : _sock(sock)
{
}

void PipeManager::addPipe(const Pipe & pipe)
{
	locked_container<std::vector<std::reference_wrapper<const Pipe>>> pipes = _pipes;
	std::vector<std::reference_wrapper<const Pipe>> _pipes = pipes;
	_pipes.push_back(pipe);
}

void PipeManager::clearPipes()
{
	locked_container<std::vector<std::reference_wrapper<const Pipe>>> pipes = _pipes;
	std::vector<std::reference_wrapper<const Pipe>> _pipes = pipes;
	_pipes.clear();
}

void PipeManager::write(buffer buf)
{
	locked_container<std::vector<std::reference_wrapper<const Pipe>>> pipes = _pipes;
	std::vector<std::reference_wrapper<const Pipe>> _pipes = pipes;
	//Piping it up
	for (auto pipe : _pipes)
	{
		buf = pipe.get().write(buf);
	}


	//Set up for like ya know sending the stuff
	union byteint
	{
		byte b[4];
		unsigned int ia;
	};

	byteint length = { buf.size() };
	char* data = new char[buf.size() + 4];

	for (int i = 0; i < 4; data[i] = length.b[3 - i], i++);
	for (unsigned int i = 0; i < buf.size(); data[i + 4] = buf[i], i++);

	length.ia += 4;
	//Sending the thingy
	int pos = 0;
	do
	{
		int result = send(_sock, data + pos, length.ia, 0);
		if (result == INVALID_SOCKET)
		{
			throw std::exception("Error while sending data to socket");
		}
		pos += result;
		length.ia -= result;
	} while (length.ia > 0);
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
	locked_container<std::vector<std::reference_wrapper<const Pipe>>> pipes = _pipes;
	std::vector<std::reference_wrapper<const Pipe>> _pipes = pipes;
	char* len = recive(_sock, 4);
	unsigned int length = len[0] << 24 | len[1] << 16 | len[2] << 8 | len[3];
	delete len;

	char* chars = recive(_sock, length);
	//First I recive them bytes

	//moving the things to buff
	buffer buf;
	for (unsigned int i = 0; i < length; buf.push_back(chars[i++]));
	delete chars;

	//piping the things
	for(auto rit = _pipes.rbegin(); rit != _pipes.rend(); ++rit)
		buf = rit->get().read(buf);

	byte id = buf[0];
	length = buf[1] << 24 | buf[2] << 16 | buf[3] << 8 | buf[4];
	buf.erase(buf.begin(), buf.begin() + 5);

	if (length != buf.size())
		throw std::exception("Buffer size and length size mismatch");

	return Request(getEnumFromID(id), time(0), buf);
}