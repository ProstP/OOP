#include "CUrlParsingError.h"

const std::string INVALID_URL = "Invalid Url.";
const std::string INVALID_DOMAIN = "Invalid domain. Domain can has letters and symbols: '-', '.', ','";
const std::string INVALID_PROTOCOL = "Invalid Protocol. Protocal must be http or https";
const std::string INVALID_PORT = "Invalid Port. Port must be between 1 and 65535";
const std::string INVALID_DOCUMENT = "Invalid document. Document can not has spaces";

CUrlParsingError CUrlParsingError::InvalidUrl()
{
	return CUrlParsingError(INVALID_URL);
}

CUrlParsingError CUrlParsingError::InvalidProtocol()
{
	return CUrlParsingError(INVALID_PROTOCOL);
}

CUrlParsingError CUrlParsingError::InvalidDomain()
{
	return CUrlParsingError(INVALID_DOMAIN);
}

CUrlParsingError CUrlParsingError::InvalidPort()
{
	return CUrlParsingError(INVALID_PORT);
}

CUrlParsingError CUrlParsingError::InvalidDocument()
{
	return CUrlParsingError(INVALID_DOCUMENT);
}

CUrlParsingError::CUrlParsingError(const std::string& message)
	: invalid_argument(message)
{
}
