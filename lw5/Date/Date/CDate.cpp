#include "CDate.h"
#include <map>

namespace
{
const unsigned MIN_YEAR = 1970;
const unsigned DAY_IN_YEAR = 365;
const unsigned DAY_IN_LEAP_YEAR = 366;
const unsigned MONTH_IN_YEAR = 12;
const unsigned DAY_IN_WEEK = 7;
}

CDate::CDate(unsigned day, Month month, unsigned year)
{
	m_timeStap = CalculateDayCountByYear(year);
	m_timeStap += CalculateDayCountByMonth(month, year % 4 == 0);
	m_timeStap += day;
}

CDate::CDate(unsigned timeStap)
	: m_timeStap{ timeStap }
{
}

CDate::CDate()
{
	m_timeStap = 0;
}

unsigned CDate::GetDay() const
{
	return 0;
}

Month CDate::GetMonth() const
{
	return Month();
}

unsigned CDate::GetYear() const
{
	return 0;
}

WeekDay CDate::GetWeekDay() const
{
	return WeekDay();
}

unsigned CDate::CalculateDayCountByYear(unsigned year) const
{
	// Доработать
	if (year < MIN_YEAR)
	{
		throw std::invalid_argument("Invalid year");
	}
	year -= MIN_YEAR;
	int days;
	if (year <= 2)
	{
		days = year * DAY_IN_YEAR;
		return days;
	}
	days = 2 * DAY_IN_YEAR + DAY_IN_LEAP_YEAR;
	year -= 3;
	unsigned leapYear = year / 4;
	unsigned yearInFour = year % 4;
	days = days + leapYear * (3 * DAY_IN_YEAR + DAY_IN_LEAP_YEAR) + yearInFour * DAY_IN_YEAR;
	return days;
}

unsigned CDate::CalculateDayCountByMonth(Month month, bool isLeap) const
{
	unsigned fullMonth = (unsigned)month - 1;
	unsigned pair = fullMonth / 2;
	unsigned inPair = fullMonth % 2;
	unsigned days = pair * (30 + 31);
	if (month > Month::FEBRUARY)
	{
		days -= (isLeap ? 1 : 2);
	}
	days += (month > Month::AUGUST ? 1 : 0);
	days += (inPair * (month < Month::AUGUST ? 31 : 30));
	return days;
}
