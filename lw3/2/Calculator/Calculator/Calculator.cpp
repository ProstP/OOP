#include "Calculator.h"
#include "Commands.h"
#include <string>

void Calculator::Var(const std::string& identifier)
{
	if (IsIdentifierUsing(identifier))
	{
		throw std::invalid_argument("Identifier already used");
	}
	m_vars[identifier] = NAN;
}

void Calculator::Let(const std::string& identifier, const std::string& value)
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
		auto GetValue = CreateFnGetValueByIdentifier();
		m_vars[identifier] = m_funcs.at(value).Execute(GetValue);
		return;
	}
	try
	{
		double result = std::stod(value);
		m_vars[identifier] = result;
	}
	catch (...)
	{
		throw std::invalid_argument("Invalid value");
	}
}

void Calculator::FnUnary(const std::string& identifier, const std::string valueIdentifier)
{
	if (IsIdentifierUsing(identifier))
	{
		throw std::invalid_argument("Identifier already used");
	}
	if (!IsIdentifierUsing(valueIdentifier))
	{
		throw std::invalid_argument("Unknown argument");
	}

	Function func(valueIdentifier);
	m_funcs[identifier] = func;
}

void Calculator::FnBinary(const std::string& identifier, const std::string& firstIdentifier, const Operations& operation, const std::string& secondIdentifier)
{
	if (IsIdentifierUsing(identifier))
	{
		throw std::invalid_argument("Identifier already used");
	}
	if (!IsIdentifierUsing(firstIdentifier) || !IsIdentifierUsing(secondIdentifier))
	{
		throw std::invalid_argument("Unknown argument");
	}
	Function func(firstIdentifier, operation, secondIdentifier);
	m_funcs[identifier] = func;
}

double Calculator::GetValueByIdentifier(std::string identifier) const
{
	if (m_vars.contains(identifier))
	{
		return m_vars.at(identifier);
	}
	if (m_funcs.contains(identifier))
	{
		auto GetValue = CreateFnGetValueByIdentifier();
		return m_funcs.at(identifier).Execute(GetValue);
	}

	throw std::runtime_error("Unknown identifier");
}

void Calculator::ExecuteFnToAllVars(std::function<void(std::string, double)>& fn) const
{
	for (auto& [identifier, value] : m_vars)
	{
		fn(identifier, value);
	}
}

void Calculator::ExecuteFnToAllFncs(std::function<void(std::string, double)>& fn) const
{
	auto GetValue = CreateFnGetValueByIdentifier();

	for (auto& [identifier, func] : m_funcs)
	{
		fn(identifier, func.Execute(GetValue));
	}
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
	return false;
}

std::function<double(std::string)> Calculator::CreateFnGetValueByIdentifier() const
{
	auto fn = [&](std::string identifier)
	{
		return GetValueByIdentifier(identifier);
	};

	return fn;
}
