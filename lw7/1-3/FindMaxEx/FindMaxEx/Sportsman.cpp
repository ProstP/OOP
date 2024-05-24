#include "Sportsman.h"

bool CompareByHeight(const Sportsman& first, const Sportsman& second)
{
	return first.height < second.height;
}

bool CompareByWeight(const Sportsman& first, const Sportsman& second)
{
	return first.weight < second.weight;
}
