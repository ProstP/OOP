#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../PrimeNumbers/GeneratePrimeNumbers.h"

SCENARIO("Get prime numbers to upper bound")
{
	WHEN("Upper bound is negative")
	{
		THEN("Will be throw exception")
		{
			CHECK_THROWS_WITH(GeneratePrimeNumbersSet(-1), "Upper bound must be more then 1\n");
		}
	}

	WHEN("Upper bound more then max acceptable")
	{
		THEN("Will catch exception")
		{
			CHECK_THROWS_WITH(GeneratePrimeNumbersSet(1000000001), "You have exceeded the maximum value of the upper bound\n");
		}
	}

	WHEN("Upper bound is 1")
	{
		THEN("Will be throw exception")
		{
			CHECK_THROWS_WITH(GeneratePrimeNumbersSet(1), "Upper bound must be more then 1\n");
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

	WHEN("Upper bound is 10000")
	{
		THEN("Set will has 1229 elements")
		{
			auto primeNums = GeneratePrimeNumbersSet(10000);
			CHECK(primeNums.size() == 1229);
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
}