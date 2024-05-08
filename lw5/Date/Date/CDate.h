#pragma once
#include "Month.h"
#include "WeekDay.h"
#include <iostream>

class CDate
{
public:
	CDate(unsigned day, Month month, unsigned year);
	explicit CDate(unsigned timeStamp);
	CDate();
	unsigned GetDay() const;
	Month GetMonth() const;
	unsigned GetYear() const;
	WeekDay GetWeekDay() const;
	CDate& operator++();
	CDate operator++(int) const;
	CDate& operator--();
	CDate operator--(int) const;
	CDate operator+(unsigned value) const;
	friend CDate operator+(unsigned value, const CDate& date);
	CDate operator-(unsigned value) const;
	unsigned operator-(const CDate& date) const;
	CDate& operator+=(unsigned value);
	CDate& operator-=(unsigned value);
	friend std::ostream& operator<<(std::ostream& out, const CDate& date);
	friend std::istream& operator>>(std::istream& in, CDate& date);
	bool operator!=(const CDate& date) const;
	bool operator==(const CDate& date) const;
	bool operator<(const CDate& date) const;
	bool operator>(const CDate& date) const;
	bool operator<=(const CDate& date) const;
	bool operator>=(const CDate& date) const;

private:
	unsigned m_timeStamp;
	unsigned CalculateDayCountByYear(unsigned year) const;
	unsigned CalculateDayCountByMonth(Month month, bool isLeap = false) const;
	unsigned GetDayCountInMonth(Month month, bool isLoop = false) const;
	void CheckDayAndMonthToValid(unsigned day, Month month, bool isLeap = false) const;
	static bool CheckYearIsLeap(unsigned year);
};
