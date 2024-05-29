#include <iostream>
#include "CMyArray.h"
#include <vector>

int main()
{
	CMyArray<std::string> arr;
	std::vector<std::string> vector;
	arr.AddToBack("Some");
	arr.AddToBack("text");
	arr.AddToBack("!!!!");
	std::copy(arr.rbegin(), arr.rend(), std::back_inserter(vector));
}