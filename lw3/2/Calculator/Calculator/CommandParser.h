#pragma once
#include "Calculator.h"
#include <regex>

class CommandParser
{
public:
	CommandParser(Calculator& calculator);
	void Handle(std::istream& in, std::ostream& out);

private:
	Calculator m_calculator;
	void DefineCommand(const std::string& str, std::ostream& out);
	void ParseCommand(const std::regex& pattern, std::smatch& match, const std::string& command);
	void VarCommand(const std::string& identifier);
	void LetCommand(const std::string& identifier, const std::string& value);
	void FnCommand(const std::string& identifier, const std::string& arg1, const std::string& operation, const std::string& arg2);
	void PrintCommand(const std::string& identifier, std::ostream& out);
	void PrintVarsCommand(std::ostream& out);
	void PrintFnsCommand(std::ostream& out);
};
