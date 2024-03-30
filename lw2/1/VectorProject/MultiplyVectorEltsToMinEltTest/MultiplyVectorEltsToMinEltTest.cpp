#include <iostream>
#include <sstream>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../../../../../catch.hpp"
#include "../MultiplyVectorEltsToMinElt/MultiplyToMinElt.h"

SCENARIO("Create vector")
{
	WHEN("Input is empty")
	{
		std::istringstream input("");
		THEN("Vector length = 0")
		{
			std::vector<float> vector = ReadVector(input);
			CHECK(vector.empty());
		}
	}

	WHEN("Input contain values")
	{
		std::istringstream input("12 22.4554 123 654 100000");
		THEN("Vector will be contain the same num of values")
		{
			std::vector<float> vector = ReadVector(input);
			CHECK(vector.size() == 5);
		}
	}
}

SCENARIO("Print vector")
{
	WHEN("Vector is empty")
	{
		std::istringstream input("");
		std::ostringstream output;
		THEN("Output is empty")
		{
			std::vector<float> vector = ReadVector(input);
			PrintVector(vector, output);
			CHECK(output.str().empty());
		}
	}

	WHEN("Vector contain values")
	{
		std::istringstream input("12 22.4554 123 654 100000");
		std::ostringstream output;
		THEN("Output contains value form vector")
		{
			std::vector<float> vector = ReadVector(input);
			PrintVector(vector, output);
			CHECK(output.str() == "12.00 22.46 123.00 654.00 100000.00");
		}
	}
}

SCENARIO("Multiply elements in vector to min element in vector")
{
	WHEN("Vector is empty")
	{
		std::istringstream input("");
		std::ostringstream output;
		THEN("Output is empty")
		{
			std::vector<float> vector = ReadVector(input);
			MultiplyEltsToMinElt(vector);
			PrintVector(vector, output);
			CHECK(output.str().empty());
		}
	}

	WHEN("Vector contain values")
	{
		std::istringstream input("12 22.4554 123 654 100000 5 15.234324");
		std::ostringstream output;
		THEN("Output contains value form vector")
		{
			std::vector<float> vector = ReadVector(input);
			MultiplyEltsToMinElt(vector);
			PrintVector(vector, output);
			CHECK(output.str() == "25.00 60.00 76.17 112.28 615.00 3270.00 500000.00");
		}
	}

	WHEN("Vecor elt exceeded max acceptable value")
	{
		std::istringstream input("12 22.4554 123 654 100000 5 340000000000000000000000000000000000000");
		THEN("Will be throw exception")
		{
			std::vector<float> vector = ReadVector(input);
			CHECK_THROWS_WITH(MultiplyEltsToMinElt(vector), "7 element exceeded max acceptable value at multiply\n");
		}
	}
}
