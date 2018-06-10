#include "RequestResult.h"

RequestResult::RequestResult(buffer buffer, IRequestHandler* handler) : _response(buffer), _newHandler(handler)
{
}

buffer RequestResult::getBuffer()
{
	return _response;
}

IRequestHandler * RequestResult::getNewHandler()
{
	return _newHandler;
}
