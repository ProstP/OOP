#include <iostream>
#include <iterator>
#include "GeneratePrimeNumbers.h"
#include <string>
#include <ctime>

struct Args
{
	int upperBound;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::runtime_error("Invalid arguments count\nUsage: PrintNumbers.exe <upperBound>\n");
	}
	int upperBound = std::stoi(argv[1]);
	return Args{ upperBound };
}

int main(int argc, char* argv[])
{
	try
	{
		clock_t start = clock();
		Args args = ParseArgs(argc, argv);
		std::set<int> primeNums = GeneratePrimeNumbersSet(args.upperBound);
		std::cout << primeNums.size() << "\n";
		//std::copy(primeNums.begin(), primeNums.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << (clock() - start) / (float)CLOCKS_PER_SEC << "\n";
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}