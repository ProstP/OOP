#include "CStringList.h"
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	CStringList list;
	list.AddStrToEnd("Some");
	list.AddStrToEnd("text");
	std::for_each(list.begin(), list.end(), [](const std::string& str)
		{
			std::cout << str << "\n";
		});
}
