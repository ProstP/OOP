#include "CommandParser.h"
#include "Commands.h"
#include <iomanip>
#include <string>
#include <set>

namespace {
	const int PRECISION = 2;
}

CommandParser::CommandParser(Calculator& calculator)
	: m_calculator(calculator)
{
}

void CommandParser::Handle(std::istream& in, std::ostream& out)
{
	std::string line;
	while (std::getline(in, line))
	{
		if (line == EXIT_COMMAND)
		{
			break;
		}
		try
		{
			DefineCommand(line, out);
		}
		catch (const std::exception& e)
		{
			out << e.what() << "\n";
		}
	}
}

void CommandParser::DefineCommand(const std::string& str, std::ostream& out)
{
	if (str.find(PRINTVARS_COMMAND) != std::string::npos)
	{
		std::smatch match;
		ParseCommand(std::regex("^(printvars)$"), match, str);
		PrintVarsCommand(out);
	}
	else if (str.find(PRINTFNS_COMMAND) != std::string::npos)
	{
		std::smatch match;
		ParseCommand(std::regex("^(printfns)$"), match, str);
		PrintFnsCommand(out);
	}
	else if (str.find(VAR_COMMAND) != std::string::npos)
	{
		std::smatch match;
		ParseCommand(std::regex("^(var)\\s+([A-Za-z]\\w*)$"), match, str);
		VarCommand(match[2].str());
	}
	else if (str.find(LET_COMMAND) != std::string::npos)
	{
		std::smatch match;
		ParseCommand(std::regex("^(let)\\s+([A-Za-z]\\w*)\\s*=\\s*([\\-?\\w\.]+)$"), match, str);
		LetCommand(match[2].str(), match[3].str());
	}
	else if (str.find(FN_COMMAND) != std::string::npos)
	{
		std::smatch match;
		ParseCommand(std::regex("^(fn)\\s+([A-Za-z]\\w*)\\s*=\\s*(\\w+)\\s*([\\+\\-\\*\\/])?\\s*(\\w+)?$"), match, str);
		FnCommand(match[2].str(), match[3].str(), match[4].str(), match[5].str());
	}
	else if (str.find(PRINT_COMMAND) != std::string::npos)
	{
		std::smatch match;
		ParseCommand(std::regex("^(print)\\s+(\\w+)$"), match, str);
		PrintCommand(match[2].str(), out);
	}
	else
	{
		out << "Unknown command\n";
	}
}

void CommandParser::ParseCommand(const std::regex& pattern, std::smatch& match, const std::string& command) const
{
	if (!std::regex_match(command, match, pattern))
	{
		throw std::runtime_error("Invalid command");
	}
}

void CommandParser::VarCommand(const std::string& identifier)
{
	CheckIdentifierWithReservedWords(identifier);
	m_calculator.Var(identifier);
}

void CommandParser::LetCommand(const std::string& identifier, const std::string& value)
{
	CheckIdentifierWithReservedWords(identifier);
	m_calculator.Let(identifier, value);
}

void CommandParser::FnCommand(const std::string& identifier, const std::string& arg1, const std::string& operation, const std::string& arg2)
{
	CheckIdentifierWithReservedWords(identifier);
	if (arg2.empty())
	{
		m_calculator.FnUnary(identifier, arg1);
		return;
	}

	const std::map<std::string, Operations> OperationsFromStr{
		{ "+", Operations::ADD },
		{ "-", Operations::SUB },
		{ "*", Operations::MUL },
		{ "/", Operations::DIV }
	};

	m_calculator.FnBinary(identifier, arg1, OperationsFromStr.at(operation), arg2);
}

void CommandParser::PrintCommand(const std::string& identifier, std::ostream& out) const
{
	out << std::fixed << std::setprecision(PRECISION);

	double value = m_calculator.GetValueByIdentifier(identifier);
	if (std::isnan(value))
	{
		out << "Nan";
	}
	else
	{
		out << value;
	}
	out << std::endl;
}

void CommandParser::PrintVarsCommand(std::ostream& out) const
{
	out << std::fixed << std::setprecision(PRECISION);
	auto fn = CreateFnToPrintValue(out);

	m_calculator.ExecuteFnToAllVars(fn);
}

void CommandParser::PrintFnsCommand(std::ostream& out) const
{
	out << std::fixed << std::setprecision(PRECISION);
	auto fn = CreateFnToPrintValue(out);

	m_calculator.ExecuteFnToAllFncs(fn);
}

void CommandParser::CheckIdentifierWithReservedWords(const std::string& identifier) const
{
	std::set<std::string> ReservedWords = {
	VAR_COMMAND, LET_COMMAND, PRINT_COMMAND, PRINTVARS_COMMAND, PRINTFNS_COMMAND};

	if (ReservedWords.contains(identifier))
	{
		throw std::invalid_argument("Identifier has already been reserved");
	}
}

std::function<void(std::string, double)> CommandParser::CreateFnToPrintValue(std::ostream& out) const
{
	auto fn = [&out](std::string identifier, double value)
	{
		out << identifier << ":";
		if (std::isnan(value))
		{
			out << "Nan";
		}
		else
		{
			out << value;
		}
		out << std::endl;
	};

	return fn;
}
