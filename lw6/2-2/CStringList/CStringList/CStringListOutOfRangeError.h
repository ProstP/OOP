#pragma once
#include <iostream>

class CStringListOutOfRangeError : public std::out_of_range
{
public:
	CStringListOutOfRangeError(std::string message)
		: std::out_of_range(move(message)){};
};
