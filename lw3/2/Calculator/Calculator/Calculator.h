#pragma once
#include "Function.h"
#include <iostream>
#include <map>
#include <set>

class Calculator
{
public:
	void Var(const std::string& identifier);
	void Let(const std::string& identifier, const std::string& value);
	void FnUnary(const std::string& identifier, const std::string& valueIdentifier);
	void FnBinary(const std::string& identifier, const std::string& firstIdentifier, const Operations& operation, const std::string& secondIdentifier);
	double GetValueByIdentifier(const std::string& identifier) const;
	void ExecuteFnToAllVars(std::function<void(std::string, double)>& fn) const;
	void ExecuteFnToAllFncs(std::function<void(std::string, double)>& fn) const;

private:
	std::map<std::string, double> m_vars;
	std::map<std::string, Function> m_funcs;
	bool IsIdentifierUsing(const std::string& identifier);
	std::function<double(std::string)> CreateFnGetValueByIdentifier() const;
};
