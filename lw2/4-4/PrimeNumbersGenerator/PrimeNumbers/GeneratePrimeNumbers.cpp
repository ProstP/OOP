#include "GeneratePrimeNumbers.h"
#include <iostream>
#include <vector>
#include <ctime>

void CrossOutEvenNumbers(std::vector<bool>& numbers, int upperBound)
{
	for (int i = 4; i <= upperBound; i += 2)
	{
		numbers[i] = false;
	}
}

void CrossOutMultiplesNumbers(std::vector<bool>& numbers, int multiply, int upperBound)
{
	if (multiply > upperBound / multiply)
	{
		return;
	}

	for (int i = multiply * multiply; i <= upperBound; i += multiply)
	{
		if (numbers[i])
		{
			numbers[i] = false;
		}
	}
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound <= 1)
	{
		throw std::runtime_error("Upper bound must be more then 1\n");
	}
	const int maxBound = 1000000000;
	if (upperBound > maxBound)
	{
		throw std::runtime_error("You have exceeded the maximum value of the upper bound\n");
	}

	std::vector<bool> numbers(upperBound + 1, true);
	numbers[0] = numbers[1] = false;
	CrossOutEvenNumbers(numbers, upperBound);

	std::set<int> primeNums;
	primeNums.insert(2);
	for (int i = 3; i <= upperBound; i += 2)
	{
		if (numbers[i])
		{
			primeNums.insert(i);
			CrossOutMultiplesNumbers(numbers, i, upperBound);
		}
	}

	return primeNums;
}
