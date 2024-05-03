#include "CDate.h"
#include <iomanip>
#include <string>

namespace
{
const unsigned MIN_YEAR = 1970;
const unsigned MAX_YEAR = 9999;
const unsigned DAY_IN_YEAR = 365;
const unsigned DAY_IN_LEAP_YEAR = 366;
const unsigned MONTH_IN_YEAR = 12;
const unsigned DAY_IN_WEEK = 7;
} // namespace

CDate::CDate(unsigned day, Month month, unsigned year)
{
	CheckDayAndMonthToValid(day, month, year % 4 == 0);
	m_timeStamp = CalculateDayCountByYear(year);
	m_timeStamp += CalculateDayCountByMonth(month, year % 4 == 0);
	m_timeStamp += (day - 1);
}

CDate::CDate(unsigned timeStamp)
	: m_timeStamp{ timeStamp }
{
	if (m_timeStamp > CalculateDayCountByYear(MAX_YEAR) + DAY_IN_YEAR)
	{
		throw std::out_of_range("Date exceeded max date value");
	}
}

CDate::CDate()
{
	m_timeStamp = 0;
}

unsigned CDate::GetDay() const
{
	unsigned year = GetYear();
	return m_timeStamp - CalculateDayCountByYear(year) - CalculateDayCountByMonth(GetMonth(), year % 4 == 0) + 1;
}

Month CDate::GetMonth() const
{
	unsigned days = m_timeStamp;
	unsigned year = GetYear();
	days = days - CalculateDayCountByYear(year) + 1;
	unsigned daysInMonth = GetDayCountInMonth(Month::JANUARY);
	unsigned monthCount = (unsigned)Month::JANUARY;
	while (days > daysInMonth && monthCount != (unsigned)Month::DECEMBER)
	{
		monthCount++;
		daysInMonth += GetDayCountInMonth((Month)monthCount, year % 4 == 0);
	}
	return (Month)monthCount;
}

unsigned CDate::GetYear() const
{
	if (m_timeStamp < DAY_IN_YEAR * 2)
	{
		unsigned year = m_timeStamp / DAY_IN_YEAR;
		return MIN_YEAR + year;
	}
	else if (m_timeStamp < DAY_IN_YEAR * 2 + DAY_IN_LEAP_YEAR)
	{
		return MIN_YEAR + 2;
	}
	unsigned year = 3;
	unsigned days = m_timeStamp - DAY_IN_YEAR * 2 - DAY_IN_LEAP_YEAR;
	unsigned leapYears = days / (DAY_IN_YEAR * 3 + DAY_IN_LEAP_YEAR);
	unsigned daysInFour = days % (DAY_IN_YEAR * 3 + DAY_IN_LEAP_YEAR);
	unsigned yearInFour = daysInFour / DAY_IN_YEAR;
	yearInFour -= yearInFour == 4 ? 1 : 0;
	return MIN_YEAR + year + leapYears * 4 + yearInFour;
}

WeekDay CDate::GetWeekDay() const
{
	return (WeekDay)((m_timeStamp + (unsigned)WeekDay::THURSDAY) % 7);
}

CDate& CDate::operator++()
{
	if (GetYear() == MAX_YEAR && GetMonth() == Month::DECEMBER && GetDay() == 31)
	{
		throw std::out_of_range("Date exceeded max date value");
	}
	++m_timeStamp;
	return *this;
}

CDate CDate::operator++(int) const
{
	CDate date(m_timeStamp);
	++date;
	return date;
}

CDate& CDate::operator--()
{
	if (GetYear() == MIN_YEAR && GetMonth() == Month::JANUARY && GetDay() == 1)
	{
		throw std::out_of_range("Date bellow min date value");
	}
	--m_timeStamp;
	return *this;
}

CDate CDate::operator--(int) const
{
	CDate date(m_timeStamp);
	--date;
	return date;
}

CDate CDate::operator+(unsigned value) const
{
	CDate date(m_timeStamp + value);
	return date;
}

CDate operator+(unsigned value, const CDate& date)
{
	return date + value;
}

CDate CDate::operator-(unsigned value) const
{
	if (value > m_timeStamp)
	{
		throw std::out_of_range("Date bellow min date value");
	}
	return CDate(m_timeStamp - value);
}

unsigned CDate::operator-(const CDate& date) const
{
	return m_timeStamp - date.m_timeStamp;
}

CDate& CDate::operator+=(unsigned value)
{
	if (m_timeStamp + value > CalculateDayCountByYear(MAX_YEAR) + DAY_IN_YEAR)
	{
		throw std::out_of_range("Date exceeded max date value");
	}

	m_timeStamp += value;
	return *this;
}

CDate& CDate::operator-=(unsigned value)
{
	if (value > m_timeStamp)
	{
		throw std::out_of_range("Date bellow min date value");
	}
	m_timeStamp -= value;
	return *this;
}

std::ostream& operator<<(std::ostream& out, const CDate& date)
{
	out << std::setfill('0') << std::setw(2) << date.GetDay() << "." 
		<< std::setfill('0') << std::setw(2) << (unsigned)date.GetMonth() << "." 
		<< date.GetYear();
	return out;
}

std::istream& operator>>(std::istream& in, CDate& date)
{
	unsigned day, month, year;
	char ch1, ch2;
	in >> day >> ch1 >> month >> ch2 >> year;
	if (day > 31 || ch1 != '.' || month > 12 || ch2 != '.' || year > 9999 || year < 1970)
	{
		throw std::invalid_argument("Format must be dd.mm.yyyy, day <= 31, month <= 12, year 1970 - 9999");
	}
	date = CDate(day, (Month)month, year);
	return in;
}

bool CDate::operator!=(const CDate& date) const
{
	if (GetDay() != date.GetDay())
	{
		return true;
	}
	if (GetMonth() != date.GetMonth())
	{
		return true;
	}
	if (GetYear() != date.GetYear())
	{
		return true;
	}

	return false;
}

bool CDate::operator==(const CDate& date) const
{
	return !(*this != date);
}

bool CDate::operator<(const CDate& date) const
{
	if (GetYear() < date.GetYear())
	{
		return true;
	}
	if (GetYear() > date.GetYear())
	{
		return false;
	}
	if (GetMonth() < date.GetMonth())
	{
		return true;
	}
	if (GetMonth() > date.GetMonth())
	{
		return false;
	}
	if (GetDay() < date.GetDay())
	{
		return true;
	}
	if (GetDay() >= date.GetDay())
	{
		return false;
	}
}

bool CDate::operator>(const CDate& date) const
{
	if (*this == date)
	{
		return false;
	}

	return !(*this < date);
}

bool CDate::operator<=(const CDate& date) const
{
	return ((*this == date) || (*this < date));
}

bool CDate::operator>=(const CDate& date) const
{
	return ((*this == date) || (*this > date));
}

unsigned CDate::CalculateDayCountByYear(unsigned year) const
{
	if (year < MIN_YEAR)
	{
		throw std::out_of_range("Date bellow min date value");
	}
	if (year > MAX_YEAR)
	{
		throw std::out_of_range("Date exceeded max date value");
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
	days += (inPair * (month <= Month::AUGUST ? 31 : 30));
	return days;
}

unsigned CDate::GetDayCountInMonth(Month month, bool isLeap) const
{
	switch (month)
	{
	case Month::JANUARY:
	case Month::MARCH:
	case Month::MAY:
	case Month::JULY:
	case Month::AUGUST:
	case Month::OCTOBER:
	case Month::DECEMBER:
		return 31;
	case Month::APRIL:
	case Month::JUNE:
	case Month::SEPTEMBER:
	case Month::NOVEMBER:
		return 30;
	case Month::FEBRUARY:
		return (isLeap ? 29 : 28);
	};
}

void CDate::CheckDayAndMonthToValid(unsigned day, Month month, bool isLeap) const
{
	if (day > GetDayCountInMonth(month, isLeap))
	{
		throw std::out_of_range("Invalid day of month");
	}
}

/*
Month CDate::GetMonth() const
{
	//Доработать
	unsigned days = m_timeStamp;
	unsigned year = GetYear();
	days = days - CalculateDayCountByYear(year);
	if (days < 31 + (year % 4 == 0 ? 29 : 28))
	{
		return (Month)(days / 31 + 1);
	}
	days = days - (31 + (year % 4 == 0 ? 29 : 28));
	unsigned pair;
	unsigned daysInPair;
	unsigned inPair;
	if (days <= 61 * 2 + 31)
	{
		pair = days / 61;
		daysInPair = days % 61;
		inPair = daysInPair / 31;
		return (Month)(2 + pair * 2 + inPair + 1);
	}
	days -= (61 * 2);
	if (days < 62)
	{
		return Month::AUGUST;
	}
	days -= 62;

	pair = days / 61;
	daysInPair = days % 61;
	inPair = daysInPair / 30;
	return (Month)(8 + pair * 2 + inPair + 1);
}
*/
