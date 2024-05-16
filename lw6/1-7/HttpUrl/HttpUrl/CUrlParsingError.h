#pragma once
#include <iostream>

class CUrlParsingError : std::invalid_argument
{
public:
	static CUrlParsingError InvalidUrl();
	static CUrlParsingError InvalidProtocol();
private:
	CUrlParsingError(const std::string& message);
};

