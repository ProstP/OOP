#include <cctype>
#include <cmath>
#include <iostream>
#include <string>

const int MIN_RADIX = 2;
const int MAX_RADIX = 36;
const char NEGATIVE_SYMBOL = '-';

struct Args
{
	int sourceRadix;
	int destinationRadix;
	std::string value;
};

bool IsRadix(int value)
{
	if (MIN_RADIX <= value && value <= MAX_RADIX)
	{
		return true;
	}

	return false;
}

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		throw std::runtime_error("Invalid aruments count\nUsage: Radix.exe <source notation> <destination notation> <value>\n");
	}
	int source = std::stoi(argv[1]);
	int destination = std::stoi(argv[2]);
	if (!IsRadix(source) || !IsRadix(destination))
	{
		throw std::runtime_error("Notation must be in between " + std::to_string(MIN_RADIX) + " and " + std::to_string(MAX_RADIX) + "\n");
	}

	Args args;
	args.sourceRadix = source;
	args.destinationRadix = destination;
	args.value = argv[3];
	return args;
}

bool IsNegative(const std::string& str)
{
	if (str[0] == NEGATIVE_SYMBOL)
	{
		return true;
	}
	return false;
}

int CharToInt(char ch)
{
	if ('0' <= ch && ch <= '9')
	{
		return ch - '0';
	}

	if ('A' <= ch && ch <= 'Z')
	{
		return 10 + ch - 'A';
	}

	throw std::runtime_error("Invalid symbol");
}

int MultiplyAndAdd(int result, int multiplier, int summand)
{
	if (summand < 0)
	{
		if (result < (INT_MIN - summand) / multiplier)
		{
			throw std::runtime_error("The value less min acceptable value\n");
		}
	}
	else
	{
		if (result > (INT_MAX - summand) / multiplier)
		{
			throw std::runtime_error("The value bigger max acceptable value\n");
		}
	}
	result = result * multiplier + summand;

	return result;
}

int StringToInt(const std::string& str, int radix)
{
	if (str.empty())
	{
		throw std::runtime_error("Value can not be empty");
	}
	int result = 0;
	bool isNegative = IsNegative(str);

	for (int i = 0; i < str.length(); i++)
	{
		if (isNegative && i == 0)
		{
			continue;
		}

		int digit = CharToInt(str[i]);
		if (digit >= radix)
		{
			throw std::runtime_error("Digit in number can not be more then radix");
		}
		if (isNegative)
		{
			digit *= -1;
		}
		result = MultiplyAndAdd(result, radix, digit);
	}

	return result;
}

char IntToChar(int value)
{
	if (0 <= value && value <= 9)
	{
		return '0' + value;
	}
	if (10 <= value && value <= MAX_RADIX - 1)
	{
		return 'A' + value - 10;
	}
	throw std::runtime_error("Invalid digit");
}

std::string IntToString(int value, int radix)
{
	std::string result;
	bool isNegative = (value < 0);

	do
	{
		int remainder = abs(value % radix);
		char ch = IntToChar(remainder);
		value /= radix;
		result += ch;
	} while (value != 0);

	if (isNegative)
	{
		result += NEGATIVE_SYMBOL;
	}

	std::reverse(result.begin(), result.end());
	return result;
}

std::string ConvertValueFromSourceToDestinationRadix(const std::string& value, int source, int destination)
{
	int number = StringToInt(value, source);
	std::string result = IntToString(number, destination);

	return result;
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);
		std::string value = ConvertValueFromSourceToDestinationRadix(args.value, args.sourceRadix, args.destinationRadix);
		std::cout << value << "\n";
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return 1;
	}

	return 0;
}
