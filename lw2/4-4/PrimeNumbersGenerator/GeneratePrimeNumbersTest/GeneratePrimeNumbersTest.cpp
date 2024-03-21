#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../PrimeNumbers/GeneratePrimeNumbers.h"

SCENARIO("Get prime numbers to upper bound")
{
	WHEN("Upper bound less 2")
	{
		THEN("Will be throw exception")
		{
			CHECK_THROWS_WITH(GeneratePrimeNumbersSet(1), "Upper bound must be more then 1\n");
		}
	}

	WHEN("Upper bound more then max acceptable")
	{
		THEN("Will catch exception")
		{
			CHECK_THROWS_WITH(GeneratePrimeNumbersSet(1000000001), "You have exceeded the maximum value of the upper bound\n");
		}
	}

	WHEN("Upper bound is 2")
	{
		THEN("Set will has one element")
		{
			auto primeNums = GeneratePrimeNumbersSet(2);
			CHECK(primeNums.size() == 1);
		}
	}

	WHEN("Upper bound is max")
	{
		THEN("Set will has 5761455 elements")
		{
			std::set<int> primeNums = GeneratePrimeNumbersSet(100000000);
			CHECK(primeNums.size() == 5761455);
		}
	}

	WHEN("Upper bound is 100")
	{
		THEN("Set will has 25 prime numbers")
		{
			std::set<int> expected = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
				37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
			std::set<int> primeNums = GeneratePrimeNumbersSet(100);

			bool isEqual = true;
			if (expected.size() == primeNums.size())
			{
				for (auto num : primeNums)
				{
					if (!expected.contains(num))
					{
						isEqual = false;
						break;
					}
				}
			}
			else
			{
				isEqual = false;
			}
			CHECK(isEqual);
		}
	}
}
