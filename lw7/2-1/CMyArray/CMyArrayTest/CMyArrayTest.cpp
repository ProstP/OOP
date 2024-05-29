#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../CMyArray/CMyArray.h"
#include <vector>

TEST_CASE("With double")
{
	WHEN("Creating deffault")
	{
		CMyArray<double> arr;
		THEN("Size = 0, capacity = 1")
		{
			CHECK(arr.GetCount() == 0);
			CHECK(arr.GetCapacity() == 2);
		}
	}

	WHEN("Adding elts to end and getting by []")
	{
		CMyArray<double> arr;
		arr.AddToBack(5);
		arr.AddToBack(5.2222);
		arr.AddToBack(100.222);
		arr.AddToBack(220);
		THEN("Size and capacity will increase and elements in indexes will be right")
		{
			CHECK(arr.GetCount() == 4);
			CHECK(arr.GetCapacity() == 8);
			CHECK(arr[0] == 5);
			CHECK(arr[1] == 5.2222);
			CHECK(arr[2] == 100.222);
		}
	}

	WHEN("Getting by [] go outside array")
	{
		CMyArray<double> arr;
		arr.AddToBack(5);
		arr.AddToBack(5.2222);
		arr.AddToBack(100.222);
		THEN("Will trow out_of_range exception")
		{
			CHECK_THROWS_AS(arr[10], std::out_of_range);
		}
	}

	WHEN("Chenge by []")
	{
		CMyArray<double> arr;
		arr.AddToBack(5);
		arr.AddToBack(5.2222);
		arr.AddToBack(100.222);
		arr[2] = 10.001;
		THEN("In changed index will be new value")
		{
			CHECK(arr[2] == 10.001);
		}
	}

	WHEN("Enumeration elements and getting general sum")
	{
		CMyArray<double> arr;
		double digit1 = 5;
		double digit2 = 5.2222;
		double digit3 = 100.222;
		arr.AddToBack(digit1);
		arr.AddToBack(digit2);
		arr.AddToBack(digit3);
		double expectedSum = digit1 + digit2 + digit3;
		double generalSum = 0;
		for (const double value : arr)
		{
			generalSum += value;
		}
		THEN("Expected sum = sum grom elemts in array")
		{
			CHECK(expectedSum == generalSum);
		}
	}
}

TEST_CASE("With string")
{
	WHEN("Adding elts to end and getting by []")
	{
		CMyArray<std::string> arr;
		arr.AddToBack("Some");
		arr.AddToBack("text");
		arr.AddToBack("!!!!");
		THEN("Elements in indexes will be right")
		{
			CHECK(arr[0] == "Some");
			CHECK(arr[1] == "text");
			CHECK(arr[2] == "!!!!");
		}
	}

	WHEN("Copy elements from MyArray to vector")
	{
		CMyArray<std::string> arr;
		std::vector<std::string> vector;
		arr.AddToBack("Some");
		arr.AddToBack("text");
		arr.AddToBack("!!!!");
		std::copy(arr.begin(), arr.end(), std::back_inserter(vector));
		THEN("Vector will contain elements from MyArray")
		{
			CHECK(vector[0] == "Some");
			CHECK(vector[1] == "text");
			CHECK(vector[2] == "!!!!");
		}
	}

	WHEN("Reverse copy elements from MyArray to vector")
	{
		CMyArray<std::string> arr;
		std::vector<std::string> vector;
		arr.AddToBack("Some");
		arr.AddToBack("text");
		arr.AddToBack("!!!!");
		std::copy(arr.rbegin(), arr.rend(), std::back_inserter(vector));
		THEN("Vector will contain elements from MyArray")
		{
			CHECK(vector[0] == "!!!!");
			CHECK(vector[1] == "text");
			CHECK(vector[2] == "Some");
		}
	}
}

TEST_CASE("Copy MyArray")
{
	WHEN("Copy constructor")
	{
		CMyArray<std::string> arr1;
		arr1.AddToBack("Some");
		arr1.AddToBack("text");
		CMyArray<std::string> arr2(arr1);
		arr2[0] = "New";
		arr2.AddToBack("!!!");
		THEN("Value from arr1 copy to arr2")
		{
			CHECK(arr1[0] == "Some");
			CHECK(arr2[0] == "New");
			CHECK(arr2[1] == "text");
			CHECK(arr2[2] == "!!!");
			CHECK((arr2.GetCount() - arr1.GetCount() == 1));
		}
	}

	WHEN("Copy operator")
	{
		CMyArray<std::string> arr1;
		arr1.AddToBack("Some");
		arr1.AddToBack("text");
		CMyArray<std::string> arr2;
		arr2 = arr1;
		arr2[0] = "New";
		arr2.AddToBack("!!!");
		THEN("Value from arr1 copy to arr2")
		{
			CHECK(arr1[0] == "Some");
			CHECK(arr2[0] == "New");
			CHECK(arr2[1] == "text");
			CHECK(arr2[2] == "!!!");
			CHECK((arr2.GetCount() - arr1.GetCount() == 1));
		}
	}
}

TEST_CASE("Move MyArray")
{
	WHEN("Move constructor")
	{
		CMyArray<double> arr1;
		arr1.AddToBack(2.001);
		arr1.AddToBack(10.012);
		CMyArray<double> arr2(std::move(arr1));
		THEN("Values from arr1 move to arr2")
		{
			CHECK(arr1.GetCount() == 0);
			CHECK(arr2[0] == 2.001);
			CHECK(arr2[1] == 10.012);
		}
	}

	WHEN("Move opearator")
	{
		CMyArray<double> arr1;
		arr1.AddToBack(2.001);
		arr1.AddToBack(10.012);
		CMyArray<double> arr2;
		arr2 = std::move(arr1);
		THEN("Values from arr1 move to arr2")
		{
			CHECK(arr1.GetCount() == 0);
			CHECK(arr2[0] == 2.001);
			CHECK(arr2[1] == 10.012);
		}
	}
}
