#include <iostream>
#include <vector>

//Выяснить гарантии исключений
template <typename T, typename Less>
bool FindMax(const std::vector<T>& arr, T& maxValue, const Less& less)
{
	if (arr.empty())
	{
		return false;
	}

	//Избавиться от множественного кпирования
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
