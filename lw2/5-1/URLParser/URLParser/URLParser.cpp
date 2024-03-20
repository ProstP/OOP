#include <iostream>
#include "ParseURL.h"

struct Args
{
	std::string url;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::runtime_error("Invalid agruments count\nUsage: URLParser.exe <url>");
	}
	Args args{ argv[1] };
	return args;
}

int main(int argc, char* argv[])
{
	std::string host;
	std::string document;
	int port = 0;
	Protocol protocol = Protocol::HTTP;
	std::cout << ParseURL("https://habr.com/ru/companies/otus/articles/532056/", protocol, port, host, document) << " " << host << "\n";
}