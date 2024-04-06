#pragma once
#include "Operations.h"
#include <iostream>
#include <map>
#include <vector>
#include "UndefinedValue.h"

class Function
{
public:
	Function(
		const std::string& firstIdentifier = UNDEFINED_VALUE,
		const Operations& operation = Operations::NONE,
		const std::string& secondIdentifier = "");
	std::string Execute(const std::map<std::string, std::string>& vars, const std::map<std::string, Function>& funcs);

private:
	std::vector<std::string> m_identifiers;
	Operations m_operation;
	std::string GetValueWithIdentifier(const std::string& identifier,
		const std::map<std::string, std::string>& vars,
		const std::map<std::string, Function>& funcs);
};
