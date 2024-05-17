#pragma once
#include <iostream>

class CUrlParsingError : public std::invalid_argument
{
public:
	static CUrlParsingError InvalidUrl();
	static CUrlParsingError InvalidProtocol();
	static CUrlParsingError InvalidDomain();
	static CUrlParsingError InvalidPort();
	static CUrlParsingError InvalidDocument();
private:
	CUrlParsingError(const std::string& message);
};

