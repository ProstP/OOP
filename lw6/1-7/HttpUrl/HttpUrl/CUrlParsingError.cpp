#include "CUrlParsingError.h"

const std::string INVALID_URL = "Invalid Url.";
const std::string INVALID_PROTOCOL = "Invalid Protocol. Protocal must be http or https";

CUrlParsingError CUrlParsingError::InvalidUrl()
{
	return CUrlParsingError(INVALID_URL);
}

CUrlParsingError CUrlParsingError::InvalidProtocol()
{
	return CUrlParsingError(INVALID_PROTOCOL);
}

CUrlParsingError::CUrlParsingError(const std::string& message)
	: invalid_argument(message)
{
}
