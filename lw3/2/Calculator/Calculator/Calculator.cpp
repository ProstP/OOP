#include "Calculator.h"
#include "Commands.h"
#include "UndefinedValue.h"
#include <string>

Calculator::Calculator()
{
	m_usedIdentifiers = { VAR_COMMAND, LET_COMMAND, FN_COMMAND, PRINT_COMMAND, PRINTVARS_COMMAND, PRINTFNS_COMMAND };
}

void Calculator::Var(const std::string& identifier)
{
	if (IsIdentifierUsing(identifier))
	{
		throw std::invalid_argument("Identifier already used");
	}
	m_vars[identifier] = UNDEFINED_VALUE;
}

void Calculator::Let(const std::string& identifier, std::string value)
{
	if (!m_vars.contains(identifier))
	{
		Var(identifier);
	}
	if (m_vars.contains(value))
	{
		m_vars[identifier] = m_vars.at(value);
		return;
	}
	if (m_funcs.contains(value))
	{
		m_vars[identifier] = m_funcs.at(value).Execute(m_vars, m_funcs);
		return;
	}
	try
	{
		std::stod(value);
	}
	catch (...)
	{
		throw std::invalid_argument("Value must be digit or var");
	}
	m_vars[identifier] = value;
}

void Calculator::Fn(
	const std::string& identifier,
	const std::string& firstIdentifier,
	const Operations& operation,
	const std::string& secondIdentifier)
{
	if (IsIdentifierUsing(identifier))
	{
		throw std::invalid_argument("Identifier already used");
	}
	if (!IsIdentifierUsing(firstIdentifier) || (!secondIdentifier.empty() && !IsIdentifierUsing(secondIdentifier)))
	{
		throw std::invalid_argument("Unknown argument");
	}
	Function func(firstIdentifier, operation, secondIdentifier);
	m_usedIdentifiers.insert(identifier);
	m_funcs[identifier] = func;
}

double Calculator::Print(const std::string& identifier)
{
	if (m_vars.contains(identifier))
	{
		return std::stod(m_vars.at(identifier));
	}
	if (m_funcs.contains(identifier))
	{
		return std::stod(m_funcs.at(identifier).Execute(m_vars, m_funcs));
	}

	throw std::runtime_error("Unknown identifier");
}

std::map<std::string, std::string> Calculator::GetVars()
{
	return m_vars;
}

std::map<std::string, Function> Calculator::GetFuncs()
{
	return m_funcs;
}

bool Calculator::IsIdentifierUsing(const std::string& identifier)
{
	if (m_vars.contains(identifier))
	{
		return true;
	}
	if (m_funcs.contains(identifier))
	{
		return true;
	}
	if (m_usedIdentifiers.contains(identifier))
	{
		return true;
	}
	return false;
}
