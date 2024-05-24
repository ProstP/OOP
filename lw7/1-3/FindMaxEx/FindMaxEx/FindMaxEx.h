#include <iostream>
#include <vector>

template <typename T, typename Less>
bool FindMax(const std::vector<T>& arr, T& maxValue, const Less& less)
{
	if (arr.empty())
	{
		return false;
	}

	maxValue = arr[0];
	for (size_t i = 0; i < arr.size(); i++)
	{
		if (less(maxValue, arr[i]))
		{
			maxValue = arr[i];
		}
	}

	return true;
}
