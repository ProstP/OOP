#pragma once
#include "Operations.h"
#include <iostream>
#include <map>
#include <vector>
#include <functional>

class Function
{
public:
	Function(
		const std::string& firstIdentifier,
		const Operations& operation,
		const std::string& secondIdentifier);
	Function(const std::string& identifier);
	Function();
	double Execute(const std::function<double(std::string)>& GetValue) const;

private:
	std::vector<std::string> m_identifiers;
	Operations m_operation = Operations::NONE;
	double CalculateOperationResult(double firstArg, double secondArg) const;
};
