#pragma once
#include "Function.h"
#include <iostream>
#include <map>
#include <set>

class Calculator
{
public:
	Calculator();
	void Var(const std::string& identifier);
	void Let(const std::string& identifier, std::string value);
	void Fn(
		const std::string& identifier,
		const std::string& firstIdentifier,
		const Operations& operation = Operations::NONE,
		const std::string& secondIdentifier = "");
	double Print(const std::string& identifier);
	std::map<std::string, std::string> GetVars();
	std::map<std::string, Function> GetFuncs();

private:
	std::map<std::string, std::string> m_vars;
	std::map<std::string, Function> m_funcs;
	std::set<std::string> m_usedIdentifiers;
	void CheckIdentifiersForUsing(const std::string& identifier);
};
