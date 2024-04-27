#include "CommandParser.h"
#include <iostream>

int main()
{
	BodyStore store;
	CommandParser parser(store);
	parser.Handle(std::cin, std::cout);
}
