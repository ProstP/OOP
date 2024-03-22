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
		throw std::runtime_error("Invalid agruments count\nUsage: URLParser.exe <url>\n");
	}
	Args args{ argv[1] };
	return args;
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);
		std::string host, doc;
		int port = 0;
		Protocol protocol;
		ParseURL(args.url, protocol, port, host, doc);
		std::cout << args.url << "\n"
			<< "HOST: " << host << "\n"
			<< "PORT: " << port << "\n"
			<< "DOC: " << doc << "\n";
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}