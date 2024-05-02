#pragma once
#include <iostream>
#include "Month.h"
#include "WeekDay.h"

class CDate
{
public:
	CDate(unsigned day, Month month, unsigned year);
	explicit CDate(unsigned timeStap);
	CDate();
	unsigned GetDay() const;
	Month GetMonth() const;
	unsigned GetYear() const;
	WeekDay GetWeekDay() const;
private:
	unsigned m_timeStap;
	unsigned CalculateDayCountByYear(unsigned year) const;
	unsigned CalculateDayCountByMonth(Month month, bool isLeap = false) const;
};

