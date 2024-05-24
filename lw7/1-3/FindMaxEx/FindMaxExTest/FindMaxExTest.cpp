#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../FindMaxEx/FindMaxEx.h"
#include "../FindMaxEx/Sportsman.h"

TEST_CASE("Finding max value by template")
{
	WHEN("Vector is empty")
	{
		std::vector<Sportsman> empty;
		Sportsman maxValue{ "Name", 180, 90 };
		THEN("Max value not change, function return false")
		{
			CHECK(!FindMax(empty, maxValue, CompareByHeight));
			CHECK(maxValue.name == "Name");
			CHECK(maxValue.height == 180);
			CHECK(maxValue.weight == 90);
		}
	}

	WHEN("By height")
	{
		std::vector<Sportsman> sportsmans = {
			{ "Sportsman1", 180, 96 },
			{ "Sportsman2", 171, 76 },
			{ "Sportsman3", 178, 81 },
			{ "Sportsman4", 190, 93 },
			{ "Sportsman5", 161, 60 }
		};
		Sportsman maxValue;
		THEN("Max value will has sportsman with max height, function return true")
		{
			CHECK(FindMax(sportsmans, maxValue, CompareByHeight));
			CHECK(maxValue.name == "Sportsman4");
			CHECK(maxValue.height == 190);
			CHECK(maxValue.weight == 93);
		}
	}

	WHEN("By weight")
	{
		std::vector<Sportsman> sportsmans = {
			{ "Sportsman1", 180, 96 },
			{ "Sportsman2", 171, 76 },
			{ "Sportsman3", 178, 81 },
			{ "Sportsman4", 190, 93 },
			{ "Sportsman5", 161, 60 }
		};
		Sportsman maxValue;
		THEN("Max value will has sportsman with max weight, function return true")
		{
			CHECK(FindMax(sportsmans, maxValue, CompareByWeight));
			CHECK(maxValue.name == "Sportsman1");
			CHECK(maxValue.height == 180);
			CHECK(maxValue.weight == 96);
		}
	}

	WHEN("Digits")
	{
		std::vector<int> digits = { 1, 23, -90, 12, 33333, 0 };
		int maxValue;
		THEN("Max value will has max digit in vector, function = true")
		{
			CHECK(FindMax(digits, maxValue, [](const int first, const int second) { return first < second; }));
			CHECK(maxValue == 33333);
		}
	}

	WHEN("By height, one element in vector")
	{
		std::vector<Sportsman> sportsmans = { { "Name", 179, 87 } };
		Sportsman maxValue;
		THEN("Max value = element in vector, fn = true")
		{
			CHECK(FindMax(sportsmans, maxValue, CompareByHeight));
			CHECK(maxValue.name == "Name");
			CHECK(maxValue.height == 179);
			CHECK(maxValue.weight == 87);
		}
	}

	WHEN("By weight, one element in vector")
	{
		std::vector<Sportsman> sportsmans = { { "Name", 179, 87 } };
		Sportsman maxValue;
		THEN("Max value = element in vector, fn = true")
		{
			CHECK(FindMax(sportsmans, maxValue, CompareByWeight));
			CHECK(maxValue.name == "Name");
			CHECK(maxValue.height == 179);
			CHECK(maxValue.weight == 87);
		}
	}

	WHEN("One element, digits")
	{
		std::vector<int> digits = { -1 };
		int maxValue;
		THEN("Max value = element in vector, fn = true")
		{
			CHECK(FindMax(digits, maxValue, [](const int first, const int second) { return first < second; }));
			CHECK(maxValue == -1);
		}
	}
}
