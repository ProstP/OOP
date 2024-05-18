#pragma once
#include <iostream>

class CUrlParsingError : public std::invalid_argument
{
public:
	CUrlParsingError(const std::string& message);
};

