#include "GeneratePrimeNumbers.h"
#include <ctime>
#include <iostream>
#include <vector>

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
		throw std::out_of_range("Upper bound must be more then 1\n");//Типы исключений
	}
	const int maxBound = 100'000'000;
	if (upperBound > maxBound)
	{
		throw std::out_of_range("You have exceeded the maximum value of the upper bound\n");
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
