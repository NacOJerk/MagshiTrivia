#pragma once

#include "consts.hpp"

class Pipe
{
public:
	virtual buffer write(buffer) const = 0;
	virtual buffer read(buffer) const = 0;
};

