#include <iostream>
#include "CommandParser.h"

int main()
{
	Calculator calculator;
	CommandParser commandParser(calculator);
	commandParser.Handle(std::cin, std::cout);
}