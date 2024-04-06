#include "Function.h"
#include <string>
#include "UndefinedValue.h"

Function::Function(const std::string& firstIdentifier, const Operations& operation, const std::string& secondIdentifier)
{
	m_identifiers.push_back(firstIdentifier);
	m_operation = operation;
	if (m_operation != Operations::NONE)
	{
		m_identifiers.push_back(secondIdentifier);
	}
}

std::string Function::Execute(const std::map<std::string, std::string>& vars, const std::map<std::string, Function>& funcs)
{
	std::string firstArgStr = GetValueWithIdentifier(m_identifiers[0], vars, funcs);
	if (firstArgStr == UNDEFINED_VALUE)
	{
		return UNDEFINED_VALUE;
	}
	double firstArg = std::stod(firstArgStr);

	if (m_operation == Operations::NONE)
	{
		return std::to_string(firstArg);
	}

	std::string secondArgStr = GetValueWithIdentifier(m_identifiers[1], vars, funcs);
	if (secondArgStr == UNDEFINED_VALUE)
	{
		return UNDEFINED_VALUE;
	}
	double secondArg = std::stod(secondArgStr);
	double result;

	switch (m_operation)
	{
	case Operations::ADD:
		result = firstArg + secondArg;
		break;
	case Operations::SUB:
		result = firstArg - secondArg;
		break;
	case Operations::MUL:
		result = firstArg * secondArg;
		break;
	case Operations::DIV:
		result = firstArg / secondArg;
		break;
	default:
		throw std::invalid_argument("Invalid operation");
		break;
	}

	return std::to_string(result);
}

std::string Function::GetValueWithIdentifier(const std::string& identifier,
	const std::map<std::string, std::string>& vars,
	const std::map<std::string, Function>& funcs)
{
	if (vars.contains(identifier))
	{
		return vars.at(identifier);
	}

	if (funcs.contains(identifier))
	{
		auto func = funcs.at(identifier);
		return func.Execute(vars, funcs);
	}

	throw std::runtime_error("Unknown identifier: " + identifier);
}
