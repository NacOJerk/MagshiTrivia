#pragma once

#include "Pipe.h"
#include "RSA.h"

class EncryptionPipe :
	public Pipe
{
	RSA::Key _key;
public:
	EncryptionPipe(RSA::Key);
	buffer write(buffer) const override;
	buffer read(buffer) const override;
};

