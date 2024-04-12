#include "Function.h"
#include <string>

Function::Function()
{
	//throw std::invalid_argument("Function must have at least 1 arg");
}

Function::Function(const std::string& identifier)
{
	if (identifier.empty())
	{
		throw std::invalid_argument("Identifier can't be empty str");
	}
	m_identifiers.push_back(identifier);
}

Function::Function(const std::string& firstIdentifier, const Operations& operation, const std::string& secondIdentifier)
{
	if (operation == Operations::NONE)
	{
		throw std::invalid_argument("Function with 2 args can't has none operation");
	}
	if (firstIdentifier.empty() || secondIdentifier.empty())
	{
		throw std::invalid_argument("Identifier can't be empty str");
	}

	m_identifiers.push_back(firstIdentifier);
	m_operation = operation;
	m_identifiers.push_back(secondIdentifier);
}

double Function::Execute(const std::function<double(std::string)>& GetValue) const
{
	double firstArg = GetValue(m_identifiers[0]);
	if (std::isnan(firstArg))
	{
		return NAN;
	}

	if (m_operation == Operations::NONE)
	{
		return firstArg;
	}

	double secondArg = GetValue(m_identifiers[1]);
	if (std::isnan(secondArg))
	{
		return NAN;
	}

	return CalculateOperationResult(firstArg, secondArg);
}

double Function::CalculateOperationResult(double firstArg, double secondArg) const
{
	switch (m_operation)
	{
	case Operations::ADD:
		return firstArg + secondArg;
	case Operations::SUB:
		return firstArg - secondArg;
	case Operations::MUL:
		return firstArg * secondArg;
	case Operations::DIV:
		return firstArg / secondArg;
	default:
		throw std::invalid_argument("Invalid operation");
	}
}
