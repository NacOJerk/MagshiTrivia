#include "EncryptionPipe.h"

EncryptionPipe::EncryptionPipe(RSA::Key key) : _key(key)
{
}

buffer EncryptionPipe::write(buffer buff) const
{
	return RSA::encrypt(buff, _key);
}

buffer EncryptionPipe::read(buffer buff) const
{
	return RSA::decrypt(buff, _key);
}
