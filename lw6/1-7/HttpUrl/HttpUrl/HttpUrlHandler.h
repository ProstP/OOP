#pragma once
#include <iostream>

class HttpUrlHandler
{
public:
	void Handle(std::istream& in, std::ostream& out);
};
