#include <iostream>
#include "HttpUrlHandler.h"

int main()
{
	HttpUrlHandler handler;
	handler.Handle(std::cin, std::cout);
}
