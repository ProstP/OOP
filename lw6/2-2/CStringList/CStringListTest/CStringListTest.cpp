#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../CStringList/CStringList.h"

TEST_CASE("Creating by deffault constructor")
{
	WHEN("Deffault construstor")
	{
		CStringList list;
		THEN("Empty, count = 0")
		{
			CHECK(list.IsEmpty());
			CHECK(list.GetCount() == 0);
		}
	}
}

TEST_CASE("Getting iter to begin and end")
{
	WHEN("Begin")
	{
		CStringList list;
		list.AddStrToBegin("Second");
		list.AddStrToBegin("First");
		auto iter = list.begin();
		THEN("Str of iter = First")
		{
			CHECK(*iter == "First");
		}
	}

	WHEN("End")
	{
		CStringList list;
		list.AddStrToEnd("First");
		list.AddStrToEnd("Second");
		auto iter = list.end();
		--iter;
		THEN("Str of iter = Second")
		{
			CHECK(*iter == "Second");
		}
	}
}

TEST_CASE("Operator []")
{
	THEN("Get str")
	{
		CStringList list;
		list.AddStrToEnd("First");
		list.AddStrToEnd("Second");
		list.AddStrToEnd("Third");
		THEN("Value will right")
		{
			CHECK(list[0] == "First");
			CHECK(list[1] == "Second");
			CHECK(list[2] == "Third");
		}
	}
}

TEST_CASE("Add by iter")
{
	WHEN("Position < length")
	{
		CStringList list;
		list.AddStrToEnd("First");
		list.AddStrToEnd("Second");
		list.AddStrToEnd("Third");
		list.AddStrToPos(list.begin() + 2, "After second");
		THEN("New element will be before iterator")
		{
			CHECK(list[1] == "Second");
			CHECK(list[2] == "After second");
			CHECK(list[3] == "Third");
			CHECK(list.GetCount() == 4);
		}
	}

	WHEN("Position > length")
	{
		CStringList list;
		list.AddStrToEnd("First");
		list.AddStrToEnd("Second");
		list.AddStrToEnd("Third");
		THEN("Will throw exception")
		{
			CHECK_THROWS_AS(list.AddStrToPos(list.begin() + 10, "Some"), CStringListOutOfRangeError);
		}
	}

	WHEN("Position = length")
	{
		CStringList list;
		list.AddStrToEnd("First");
		list.AddStrToEnd("Second");
		list.AddStrToEnd("Third");
		list.AddStrToPos(list.begin() + 3, "Some");
		THEN("Element will last")
		{
			CHECK(list[3] == "Some");
		}
	}
}

TEST_CASE("Remove string by pos")
{
	WHEN("Pos < length")
	{
		CStringList list;
		list.AddStrToEnd("First");
		list.AddStrToEnd("Second");
		list.AddStrToEnd("Third");
		list.RemoveStrInPos(list.begin() + 1);
		THEN("Element will remove")
		{
			CHECK(list[0] == "First");
			CHECK(list[1] == "Third");
			CHECK(list.GetCount() == 2);
		}
	}

	WHEN("Position > length")
	{
		CStringList list;
		list.AddStrToEnd("First");
		list.AddStrToEnd("Second");
		list.AddStrToEnd("Third");
		THEN("Will throw exception")
		{
			CHECK_THROWS_AS(list.RemoveStrInPos(list.begin() + 10), CStringListOutOfRangeError);
		}
	}

	WHEN("Position = length")
	{
		CStringList list;
		list.AddStrToEnd("First");
		list.AddStrToEnd("Second");
		list.AddStrToEnd("Third");
		THEN("Will throw exception")
		{
			CHECK_THROWS_AS(list.RemoveStrInPos(list.begin() + 3), CStringListOutOfRangeError);
		}
	}

	WHEN("Remove first")
	{
		CStringList list;
		list.AddStrToEnd("First");
		list.AddStrToEnd("Second");
		list.AddStrToEnd("Third");
		list.RemoveStrInPos(list.begin());
		THEN("First elt will remove")
		{
			CHECK(list[0] == "Second");
		}
	}
}

TEST_CASE("Clear")
{
	WHEN("List empty")
	{
		CStringList list;
		list.Clear();
		THEN("All ok")
		{
			CHECK(list.IsEmpty());
		}
	}

	WHEN("List not empty")
	{
		CStringList list;
		list.AddStrToEnd("Some");
		list.AddStrToEnd("text");
		list.Clear();
		THEN("All ok")
		{
			CHECK(list.IsEmpty());
		}
	}
}

TEST_CASE("For each elements")
{
	WHEN("Get all strings and add to one string")
	{
		std::string str1 = "So";
		std::string str2 = "me ";
		std::string str3 = "te";
		std::string str4 = "xt!";
		CStringList list;
		list.AddStrToEnd(str1);
		list.AddStrToEnd(str2);
		list.AddStrToEnd(str3);
		list.AddStrToEnd(str4);
		std::string general = str1 + str2 + str3 + str4;
		std::string result;
		for (const auto& str : list)
		{
			result += str;
		}
		THEN("General sum == result")
		{
			CHECK(general == result);
		}
	}
}
