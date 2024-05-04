#include "CDateController.h"
#include <map>

enum class Commands
{
	PRINT_ALL_DATES = 0,
	CREATE_DATE_BY_DD_MM_YYYY,
	CREATE_DATE_TIME_STAMP,
	SUM_DATE_AND_VALUE,
	INCREASE_DATE,
	INCREASE_VALUE_TO_DATE,
	SUB_DATES,
	SUB_VALUE_FROM_DATE,
	DECRASE_DATE,
	DECRASE_DATE_TO_VALUE,
	COMPARE_DATES_TO_EQUAL,
	COMPARE_DATES_STRICT_INEQUALITY,
	COMPARE_DATES_NON_STRICT_INEQUALITY
};

void CDateController::Handle(std::istream& in, std::ostream& out)
{
	unsigned command;
	PrintCommands(out);

	while (in >> command)
	{
		try
		{
			if (!DefineCommand(command, in, out))
			{
				break;
			}
		}
		catch (const std::exception& e)
		{
			out << e.what() << std::endl;
		}
	}
}

void CDateController::PrintCommands(std::ostream& out) const
{
	const std::map<Commands, std::string> COMMANDS_IN_STRING{
		{ Commands::PRINT_ALL_DATES, "Print all dates" },
		{ Commands::CREATE_DATE_BY_DD_MM_YYYY, "Create date by format dd.mm.yyyy" },
		{ Commands::CREATE_DATE_TIME_STAMP, "Create date by elapsed time since 1970" },
		{ Commands::SUM_DATE_AND_VALUE, "Calculate sum of date and digit" },
		{ Commands::INCREASE_DATE, "Inrease date" },
		{ Commands::INCREASE_VALUE_TO_DATE, "Increase date to value" },
		{ Commands::SUB_DATES, "Calculate sub dates" },
		{ Commands::SUB_VALUE_FROM_DATE, "Calculate sub value from date" },
		{ Commands::DECRASE_DATE, "Decrase date" },
		{ Commands::DECRASE_DATE_TO_VALUE, "Decrase date to value" },
		{ Commands::COMPARE_DATES_TO_EQUAL, "Compare two dates to equal" },
		{ Commands::COMPARE_DATES_STRICT_INEQUALITY, "Compare two dates with strict inequality" },
		{ Commands::COMPARE_DATES_NON_STRICT_INEQUALITY, "Compare two dates with non-strict inequality" }
	};

	for (const auto& command : COMMANDS_IN_STRING)
	{
		out << static_cast<unsigned>(command.first) << ":" << command.second << std::endl;
	}
}

bool CDateController::DefineCommand(unsigned command, std::istream& in, std::ostream& out)
{
	switch ((Commands)command)
	{
	case Commands::PRINT_ALL_DATES:
		PrintAllBodies(out);
		break;
	case Commands::CREATE_DATE_BY_DD_MM_YYYY:
		CreateDateWithDDMMYYYY(in);
		break;
	case Commands::CREATE_DATE_TIME_STAMP:
		CreateDateWithTimeStamp(in);
		break;
	case Commands::SUM_DATE_AND_VALUE:
		CalculateSumDateAndValue(in, out);
		break;
	case Commands::INCREASE_DATE:
		IncreaseDate(in);
		break;
	case Commands::INCREASE_VALUE_TO_DATE:
		IncreaseDateToValue(in);
		break;
	case Commands::SUB_DATES:
		CalculateSubDates(in, out);
		break;
	case Commands::SUB_VALUE_FROM_DATE:
		CalculateSubDateAndValue(in, out);
		break;
	case Commands::DECRASE_DATE:
		DecreaseDate(in);
		break;
	case Commands::DECRASE_DATE_TO_VALUE:
		DecreaseDateToValue(in);
		break;
	case Commands::COMPARE_DATES_TO_EQUAL:
		CompareDatesToEqual(in, out);
		break;
	case Commands::COMPARE_DATES_STRICT_INEQUALITY:
		CompareDatesToStrictInequal(in, out);
		break;
	case Commands::COMPARE_DATES_NON_STRICT_INEQUALITY:
		CompareDatesToNonStrictInequal(in, out);
		break;
	default:
		return false;
	}

	return true;
}

void CDateController::PrintAllBodies(std::ostream& out) const
{
	for (int i = 0; i < m_dates.size(); i++)
	{
		out << i << ":" << *m_dates[i] << std::endl;
	}
}

void CDateController::CreateDateWithDDMMYYYY(std::istream& in)
{
	CDate date;
	in >> date;
	m_dates.push_back(std::make_shared<CDate>(date));
}

void CDateController::CreateDateWithTimeStamp(std::istream& in)
{
	unsigned timeStamp;
	in >> timeStamp;
	CDate date(timeStamp);
	m_dates.push_back(std::make_shared<CDate>(date));
}

void CDateController::CalculateSumDateAndValue(std::istream& in, std::ostream& out) const
{
	unsigned index, value;
	in >> index >> value;
	out << *m_dates[index] + value << std::endl;
}

void CDateController::IncreaseDate(std::istream& in)
{
	unsigned index;
	in >> index;
	++*m_dates[index];
}

void CDateController::IncreaseDateToValue(std::istream& in)
{
	unsigned index, value;
	in >> index >> value;
	*m_dates[index] += value;
}

void CDateController::CalculateSubDates(std::istream& in, std::ostream& out) const
{
	unsigned index1, index2;
	in >> index1 >> index2;
	out << *m_dates[index1] - *m_dates[index2] << std::endl;
}

void CDateController::CalculateSubDateAndValue(std::istream& in, std::ostream& out) const
{
	unsigned index1, value;
	in >> index1 >> value;
	out << *m_dates[index1] - value << std::endl;
}

void CDateController::DecreaseDate(std::istream& in)
{
	unsigned index;
	in >> index;
	--*m_dates[index];
}

void CDateController::DecreaseDateToValue(std::istream& in)
{
	unsigned index, value;
	in >> index >> value;
	*m_dates[index] -= value;
}

void CDateController::CompareDatesToEqual(std::istream& in, std::ostream& out) const
{
	unsigned index1, index2;
	char ch1, ch2;
	in >> index1 >> ch1 >> ch2 >> index2;
	if ((ch1 != '!' && ch1 != '=') || ch2 != '=')
	{
		throw std::invalid_argument("Invalid equal sign");
	}
	if (ch1 == '!')
	{
		out << (*m_dates[index1] != *m_dates[index2]);
	}
	else
	{
		out << (*m_dates[index1] == *m_dates[index2]);
	}
	out << std::endl;
}

void CDateController::CompareDatesToStrictInequal(std::istream& in, std::ostream& out) const
{
	unsigned index1, index2;
	char ch;
	in >> index1 >> ch >> index2;
	if (ch != '<' && ch != '>')
	{
		throw std::invalid_argument("Invalid strict inequal sign");
	}
	if (ch == '<')
	{
		out << (*m_dates[index1] < *m_dates[index2]);
	}
	else
	{
		out << (*m_dates[index1] > *m_dates[index2]);
	}
	out << std::endl;
}

void CDateController::CompareDatesToNonStrictInequal(std::istream& in, std::ostream& out) const
{
	unsigned index1, index2;
	char ch1, ch2;
	in >> index1 >> ch1 >> ch2 >> index2;
	if ((ch1 != '<' && ch1 != '>') || ch2 != '=')
	{
		throw std::invalid_argument("Invalid non-strict inequal sign");
	}
	if (ch1 == '<')
	{
		out << (*m_dates[index1] <= *m_dates[index2]);
	}
	else
	{
		out << (*m_dates[index1] >= *m_dates[index2]);
	}
	out << std::endl;
}
