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
	bool IsValid() const;
};

