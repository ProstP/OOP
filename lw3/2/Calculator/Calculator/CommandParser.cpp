#include "CommandParser.h"
#include "Commands.h"
#include <iomanip>
#include <string>

const int PRECISION = 2;

CommandParser::CommandParser(Calculator& calculator)
{
	m_calculator = calculator;
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
{//Доработать парсер
	if (str.find(PRINTVARS_COMMAND) != std::string::npos)
	{
		PrintVarsCommand(out);
	}
	else if (str.find(PRINTFNS_COMMAND) != std::string::npos)
	{
		PrintFnsCommand(out);
	}
	else if (str.find(VAR_COMMAND) != std::string::npos)
	{
		std::smatch match;
		ParseCommand(std::regex("^(var)\\s+(\\w+)$"), match, str);
		VarCommand(match[2].str());
	}
	else if (str.find(LET_COMMAND) != std::string::npos)
	{
		std::smatch match;
		ParseCommand(std::regex("^(let)\\s+(\\w+)\\s*=\\s*([\\w\.]+)$"), match, str);
		LetCommand(match[2].str(), match[3].str());
	}
	else if (str.find(FN_COMMAND) != std::string::npos)
	{
		std::smatch match;
		ParseCommand(std::regex("^(fn)\\s+(\\w+)\\s*=\\s*(\\w+)\\s*([\\+\\-\\*\\/])?\\s*(\\w+)?$"), match, str);
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

void CommandParser::ParseCommand(const std::regex& pattern, std::smatch& match, const std::string& command)
{
	if (!std::regex_match(command, match, pattern))
	{
		throw std::runtime_error("Invalid command");
	}
}

void CommandParser::VarCommand(const std::string& identifier)
{
	m_calculator.Var(identifier);
}

void CommandParser::LetCommand(const std::string& identifier, const std::string& value)
{
	m_calculator.Let(identifier, value);
}

void CommandParser::FnCommand(const std::string& identifier, const std::string& arg1, const std::string& operation, const std::string& arg2)
{
	if (arg2.empty())
	{
		m_calculator.Fn(identifier, arg1);
		return;
	}

	const std::map<std::string, Operations> OperationsFromStr{
		{ "+", Operations::ADD },
		{ "-", Operations::SUB },
		{ "*", Operations::MUL },
		{ "/", Operations::DIV }
	};

	m_calculator.Fn(identifier, arg1, OperationsFromStr.at(operation), arg2);
}

void CommandParser::PrintCommand(const std::string& identifier, std::ostream& out)
{
	out << std::fixed << std::setprecision(PRECISION);

	out << m_calculator.Print(identifier) << "\n";
}

void CommandParser::PrintVarsCommand(std::ostream& out)
{
	out << std::fixed << std::setprecision(PRECISION);
	auto vars = m_calculator.GetVars();

	for (auto var : vars)
	{
		out << var.first << ":" << std::stod(var.second) << "\n";
	}
}

void CommandParser::PrintFnsCommand(std::ostream& out)
{
	out << std::fixed << std::setprecision(PRECISION);
	auto fncs = m_calculator.GetFuncs();

	for (auto fn : fncs)
	{
		out << fn.first << ":" << std::stod(fn.second.Execute(m_calculator.GetVars(), fncs)) << "\n";
	}
}
