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
	bool isLeap = CheckYearIsLeap(year);
	CheckDayAndMonthToValid(day, month, isLeap);
	m_timeStamp = CalculateDayCountByYear(year);
	m_timeStamp += CalculateDayCountByMonth(month, isLeap);
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
	return m_timeStamp - CalculateDayCountByYear(year) - CalculateDayCountByMonth(GetMonth(), CheckYearIsLeap(year)) + 1;
}

Month CDate::GetMonth() const
{
	unsigned days = m_timeStamp;
	unsigned year = GetYear();
	days = days - CalculateDayCountByYear(year) + 1;
	unsigned daysInMonth = GetDayCountInMonth(Month::JANUARY);
	unsigned monthCount = static_cast<unsigned>(Month::JANUARY);
	bool isLeap = CheckYearIsLeap(year);
	while (days > daysInMonth && monthCount != static_cast<unsigned>(Month::DECEMBER))
	{
		monthCount++;
		daysInMonth += GetDayCountInMonth(static_cast<Month>(monthCount), isLeap);
	}
	return static_cast<Month>(monthCount);
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
	const unsigned dayCountIn4Years = 3 * DAY_IN_YEAR + DAY_IN_LEAP_YEAR;

	if (days > 7 * dayCountIn4Years)
	{
		year += 28;
		days -= (7 * dayCountIn4Years);
		const unsigned dayCountInEveryHunredYears = 24 * dayCountIn4Years + 4 * DAY_IN_YEAR;
		const unsigned dayCountInEvery4HunredTears = 25 * dayCountIn4Years;
		const unsigned dayCountIn4HunredYears = 3 * dayCountInEveryHunredYears + dayCountInEvery4HunredTears;
		year += (days / dayCountIn4HunredYears * 400);
		days %= (dayCountIn4HunredYears);
		year += (days / dayCountInEveryHunredYears * 100);
		days %= dayCountInEveryHunredYears;
	}

	year += (days / dayCountIn4Years * 4);
	days %= dayCountIn4Years;
	unsigned yearInFour = days / DAY_IN_YEAR;
	yearInFour -= yearInFour == 4 ? 1 : 0;
	year += yearInFour;
	return MIN_YEAR + year;
}

WeekDay CDate::GetWeekDay() const
{
	return static_cast<WeekDay>((m_timeStamp + static_cast<unsigned>(WeekDay::THURSDAY)) % 7);
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
		<< std::setfill('0') << std::setw(2) << static_cast<unsigned>(date.GetMonth()) << "."
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
	date = CDate(day, static_cast<Month>(month), year);
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
	return false;
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
	const unsigned dayCountIn4Years = 3 * DAY_IN_YEAR + DAY_IN_LEAP_YEAR;
	if (year > 27)
	{
		year -= 28;
		days += (7 * dayCountIn4Years);
		const unsigned dayCountInEveryHunredYears = 24 * dayCountIn4Years + 4 * DAY_IN_YEAR;
		const unsigned dayCountInEvery4HunredTears = 25 * dayCountIn4Years;
		const unsigned dayCountIn4HunredYears = 3 * dayCountInEveryHunredYears + dayCountInEvery4HunredTears;
		days += (year / 400 * dayCountIn4HunredYears);
		year %= 400;
		days += (year / 100 * dayCountInEveryHunredYears);
		year %= 100;
	}

	unsigned leapYear = year / 4;
	unsigned yearInFour = year % 4;
	days += (leapYear * (3 * DAY_IN_YEAR + DAY_IN_LEAP_YEAR) + yearInFour * DAY_IN_YEAR);
	return days;
}

unsigned CDate::CalculateDayCountByMonth(Month month, bool isLeap) const
{
	unsigned fullMonth = static_cast<unsigned>(month) - 1;
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
	default:
		throw std::invalid_argument("Unknown month");
	};
}

void CDate::CheckDayAndMonthToValid(unsigned day, Month month, bool isLeap) const
{
	if (day > GetDayCountInMonth(month, isLeap))
	{
		throw std::out_of_range("Invalid day of month");
	}
}

bool CDate::CheckYearIsLeap(unsigned year)
{
	if (year % 400 == 0)
	{
		return true;
	}
	if (year % 100 == 0)
	{
		return false;
	}
	if (year % 4 == 0)
	{
		return true;
	}
	return false;
}
