#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../Date/CDate.h"

TEST_CASE("Creating date")
{
	WHEN("Create date using timeStap")
	{
		unsigned timeStap = 19845;
		CDate date(timeStap);

		THEN("Get valid date")
		{
			CHECK(date.GetDay() == 2);
			CHECK(date.GetMonth() == Month::MAY);
			CHECK(date.GetYear() == 2024);
			CHECK(date.GetWeekDay() == WeekDay::THURSDAY);
		}
	}

	WHEN("Create using day, month, year")
	{
		unsigned day = 2;
		Month month = Month::MAY;
		unsigned year = 2024;
		CDate date(day, month, year);
		
		THEN("Get value data")
		{
			CHECK(date.GetDay() == day);
			CHECK(date.GetMonth() == month);
			CHECK(date.GetYear() == year);
			CHECK(date.GetWeekDay() == WeekDay::THURSDAY);
		}
	}
}