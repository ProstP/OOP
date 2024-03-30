#include "MultiplyToMinElt.h"
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <string>

std::vector<float> ReadVector(std::istream& input)
{
	std::vector<float> vector;
	float value = 0;

	while (input >> value)
	{
		vector.push_back(value);
	}

	return vector;
}

void PrintVector(std::vector<float> vector, std::ostream& output)
{
	std::sort(vector.begin(), vector.end());
	output << std::fixed << std::setprecision(2);
	for (int i = 0; i < vector.size(); i++)
	{
		output << vector[i];
		if (i != vector.size() - 1)
		{
			output << " ";
		}
	}
}

void MultiplyEltsToMinElt(std::vector<float>& vector)
{
	if (vector.size() == 0)
	{
		return;
	}

	float minEltIter = *std::min_element(vector.begin(), vector.end());

	for (int i = 0; i < vector.size(); i++)
	{
		if (minEltIter > 1 && vector[i] > FLT_MAX / minEltIter)
		{
			throw std::runtime_error(std::to_string(i + 1) + " element exceeded max acceptable value at multiply\n");
		}
		vector[i] *= minEltIter;
	}
}
