#pragma once
#include <iostream>

struct Sportsman
{
	std::string name;
	int height;
	int weight;
};

bool CompareByHeight(const Sportsman& first, const Sportsman& second);
bool CompareByWeight(const Sportsman& first, const Sportsman& second);
