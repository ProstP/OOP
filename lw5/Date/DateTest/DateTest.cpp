#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../Date/CDate.h"
#include <string>

TEST_CASE("Creating date")
{
	WHEN("Creating date without parametrs")
	{
		CDate date;

		THEN("Date = 01/01/1970")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::JANUARY);
			CHECK(date.GetYear() == 1970);
			CHECK(date.GetWeekDay() == WeekDay::THURSDAY);
		}
	}

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

	WHEN("Set invalid day of month")
	{
		THEN("Will be trow exception")
		{
			CHECK_THROWS_WITH(CDate(29, Month::FEBRUARY, 2005), "Invalid day of month");
		}
	}

	WHEN("Set 29 february in year % == 4 but not leap")
	{
		CDate date(28, Month::FEBRUARY, 2101);
		++date;
		THEN("Will be trow exception")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::MARCH);
			CHECK(date.GetWeekDay() == WeekDay::TUESDAY);
		}
	}
}

TEST_CASE("Checking boundary dates")
{
	WHEN("1 January 1980")
	{
		CDate date(1, Month::JANUARY, 1980);
		THEN("01/01/1980, tu")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::JANUARY);
			CHECK(date.GetYear() == 1980);
			CHECK(date.GetWeekDay() == WeekDay::TUESDAY);
		}
	}

	WHEN("31 January 1983")
	{
		CDate date(31, Month::JANUARY, 1983);
		THEN("31/01/1983, mn")
		{
			CHECK(date.GetDay() == 31);
			CHECK(date.GetMonth() == Month::JANUARY);
			CHECK(date.GetYear() == 1983);
			CHECK(date.GetWeekDay() == WeekDay::MONDAY);
		}
	}

	WHEN("1 February 1984")
	{
		CDate date(1, Month::FEBRUARY, 1984);
		THEN("01/02/1984, we")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::FEBRUARY);
			CHECK(date.GetYear() == 1984);
			CHECK(date.GetWeekDay() == WeekDay::WEDNESDAY);
		}
	}

	WHEN("28 February 1983")
	{
		CDate date(28, Month::FEBRUARY, 1983);
		THEN("28/02/1983, mn")
		{
			CHECK(date.GetDay() == 28);
			CHECK(date.GetMonth() == Month::FEBRUARY);
			CHECK(date.GetYear() == 1983);
			CHECK(date.GetWeekDay() == WeekDay::MONDAY);
		}
	}

	WHEN("29 February 1984")
	{
		CDate date(29, Month::FEBRUARY, 1984);
		THEN("29/02/1984, wn")
		{
			CHECK(date.GetDay() == 29);
			CHECK(date.GetMonth() == Month::FEBRUARY);
			CHECK(date.GetYear() == 1984);
			CHECK(date.GetWeekDay() == WeekDay::WEDNESDAY);
		}
	}

	WHEN("1 March 1988")
	{
		CDate date(1, Month::MARCH, 1988);
		THEN("01/03/1988, tu")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::MARCH);
			CHECK(date.GetYear() == 1988);
			CHECK(date.GetWeekDay() == WeekDay::TUESDAY);
		}
	}

	WHEN("31 March 1991")
	{
		CDate date(31, Month::MARCH, 1991);
		THEN("31/03/1991, su")
		{
			CHECK(date.GetDay() == 31);
			CHECK(date.GetMonth() == Month::MARCH);
			CHECK(date.GetYear() == 1991);
			CHECK(date.GetWeekDay() == WeekDay::SUNDAY);
		}
	}
	WHEN("1 April 1986")
	{
		CDate date(1, Month::APRIL, 1986);
		THEN("01/01/1986, tu")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::APRIL);
			CHECK(date.GetYear() == 1986);
			CHECK(date.GetWeekDay() == WeekDay::TUESDAY);
		}
	}

	WHEN("30 April 2074")
	{
		CDate date(30, Month::APRIL, 2074);
		THEN("30/04/2074, mn")
		{
			CHECK(date.GetDay() == 30);
			CHECK(date.GetMonth() == Month::APRIL);
			CHECK(date.GetYear() == 2074);
			CHECK(date.GetWeekDay() == WeekDay::MONDAY);
		}
	}

	WHEN("1 May 2026")
	{
		CDate date(1, Month::MAY, 2026);
		THEN("01/05/2026, fr")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::MAY);
			CHECK(date.GetYear() == 2026);
			CHECK(date.GetWeekDay() == WeekDay::FRIDAY);
		}
	}

	WHEN("31 May 2000")
	{
		CDate date(31, Month::MAY, 2000);
		THEN("31/05/2000, wn")
		{
			CHECK(date.GetDay() == 31);
			CHECK(date.GetMonth() == Month::MAY);
			CHECK(date.GetYear() == 2000);
			CHECK(date.GetWeekDay() == WeekDay::WEDNESDAY);
		}
	}

	WHEN("1 June 2025")
	{
		CDate date(1, Month::JUNE, 2025);
		THEN("01/06/2025, su")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::JUNE);
			CHECK(date.GetYear() == 2025);
			CHECK(date.GetWeekDay() == WeekDay::SUNDAY);
		}
	}

	WHEN("30 June 2077")
	{
		CDate date(30, Month::JUNE, 2077);
		THEN("30/06/2077, wn")
		{
			CHECK(date.GetDay() == 30);
			CHECK(date.GetMonth() == Month::JUNE);
			CHECK(date.GetYear() == 2077);
			CHECK(date.GetWeekDay() == WeekDay::WEDNESDAY);
		}
	}

	WHEN("1 Jule 2020")
	{
		CDate date(1, Month::JULY, 2020);
		THEN("01/07/2020, we")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::JULY);
			CHECK(date.GetYear() == 2020);
			CHECK(date.GetWeekDay() == WeekDay::WEDNESDAY);
		}
	}

	WHEN("31 July 2009")
	{
		CDate date(31, Month::JULY, 2009);
		THEN("31/07/2009, fr")
		{
			CHECK(date.GetDay() == 31);
			CHECK(date.GetMonth() == Month::JULY);
			CHECK(date.GetYear() == 2009);
			CHECK(date.GetWeekDay() == WeekDay::FRIDAY);
		}
	}

	WHEN("1 August 1998")
	{
		CDate date(1, Month::AUGUST, 1998);
		THEN("01/08/1998, st")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::AUGUST);
			CHECK(date.GetYear() == 1998);
			CHECK(date.GetWeekDay() == WeekDay::SATURDAY);
		}
	}

	WHEN("31 August 2032")
	{
		CDate date(31, Month::AUGUST, 2032);
		THEN("31/08/2032, tu")
		{
			CHECK(date.GetDay() == 31);
			CHECK(date.GetMonth() == Month::AUGUST);
			CHECK(date.GetYear() == 2032);
			CHECK(date.GetWeekDay() == WeekDay::TUESDAY);
		}
	}

	WHEN("1 September 2019")
	{
		CDate date(1, Month::SEPTEMBER, 2019);
		THEN("01/09/2019, su")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::SEPTEMBER);
			CHECK(date.GetYear() == 2019);
			CHECK(date.GetWeekDay() == WeekDay::SUNDAY);
		}
	}

	WHEN("30 September 2069")
	{
		CDate date(30, Month::SEPTEMBER, 2069);
		THEN("30/09/2069, mn")
		{
			CHECK(date.GetDay() == 30);
			CHECK(date.GetMonth() == Month::SEPTEMBER);
			CHECK(date.GetYear() == 2069);
			CHECK(date.GetWeekDay() == WeekDay::MONDAY);
		}
	}

	WHEN("1 October 2016")
	{
		CDate date(1, Month::OCTOBER, 2016);
		THEN("01/10/2016, su")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::OCTOBER);
			CHECK(date.GetYear() == 2016);
			CHECK(date.GetWeekDay() == WeekDay::SATURDAY);
		}
	}

	WHEN("31 October 2037")
	{
		CDate date(31, Month::OCTOBER, 2037);
		THEN("31/10/2037, sa")
		{
			CHECK(date.GetDay() == 31);
			CHECK(date.GetMonth() == Month::OCTOBER);
			CHECK(date.GetYear() == 2037);
			CHECK(date.GetWeekDay() == WeekDay::SATURDAY);
		}
	}

	WHEN("1 November 2001")
	{
		CDate date(1, Month::NOVEMBER, 2001);
		THEN("01/11/2001, tr")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::NOVEMBER);
			CHECK(date.GetYear() == 2001);
			CHECK(date.GetWeekDay() == WeekDay::THURSDAY);
		}
	}

	WHEN("30 November 2043")
	{
		CDate date(30, Month::NOVEMBER, 2043);
		THEN("31/11/2043, mn")
		{
			CHECK(date.GetDay() == 30);
			CHECK(date.GetMonth() == Month::NOVEMBER);
			CHECK(date.GetYear() == 2043);
			CHECK(date.GetWeekDay() == WeekDay::MONDAY);
		}
	}

	WHEN("1 December 1998")
	{
		CDate date(1, Month::DECEMBER, 1998);
		THEN("01/12/1998, tu")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::DECEMBER);
			CHECK(date.GetYear() == 1998);
			CHECK(date.GetWeekDay() == WeekDay::TUESDAY);
		}
	}

	WHEN("31 December 2029")
	{
		CDate date(31, Month::DECEMBER, 2029);
		THEN("31/12/2029, mn")
		{
			CHECK(date.GetDay() == 31);
			CHECK(date.GetMonth() == Month::DECEMBER);
			CHECK(date.GetYear() == 2029);
			CHECK(date.GetWeekDay() == WeekDay::MONDAY);
		}
	}
}

TEST_CASE("Operator ++")
{

	WHEN("Pre++")
	{
		CDate date(31, Month::DECEMBER, 2020);
		++date;
		THEN("Year will be increase")
		{
			CHECK(date.GetYear() == 2021);
		}
	}

	WHEN("Pre++ max year")
	{
		CDate date(31, Month::DECEMBER, 9999);
		CHECK_THROWS_WITH(++date, "Date exceeded max date value");
	}

	WHEN("Post++")
	{
		CDate date(31, Month::DECEMBER, 2020);
		CDate date1 = date++;
		THEN("Year will be increase")
		{
			CHECK(date.GetYear() == 2020);
			CHECK(date1.GetYear() == 2021);
		}
	}

	WHEN("Post++ max year")
	{
		CDate date(31, Month::DECEMBER, 9999);
		CHECK_THROWS_WITH(date++, "Date exceeded max date value");
	}
}

TEST_CASE("Operator --")
{
	WHEN("Pre--")
	{
		CDate date(1, Month::JANUARY, 2020);
		--date;
		THEN("Year will be decreased")
		{
			CHECK(date.GetYear() == 2019);
		}
	}

	WHEN("Pre-- min year")
	{
		CDate date(1, Month::JANUARY, 1970);
		CHECK_THROWS_WITH(--date, "Date bellow min date value");
	}

	WHEN("Post--")
	{
		CDate date(1, Month::JANUARY, 2020);
		CDate date1 = date--;
		THEN("Year will be decreased")
		{
			CHECK(date.GetYear() == 2020);
			CHECK(date1.GetYear() == 2019);
		}
	}

	WHEN("Post-- min year")
	{
		CDate date(1, Month::JANUARY, 1970);
		CHECK_THROWS_WITH(date--, "Date bellow min date value");
	}
}

TEST_CASE("Operator +")
{
	WHEN("Date + digit")
	{
		CDate date(5, Month::FEBRUARY, 2010);
		CDate date1 = date + 400;
		THEN("Date will true")
		{
			CHECK(date1.GetDay() == 12);
			CHECK(date1.GetMonth() == Month::MARCH);
			CHECK(date1.GetYear() == 2011);
		}
	}

	WHEN("Digit + date")
	{
		CDate date(5, Month::FEBRUARY, 2010);
		CDate date1 = 400 + date;
		THEN("Date will true")
		{
			CHECK(date1.GetDay() == 12);
			CHECK(date1.GetMonth() == Month::MARCH);
			CHECK(date1.GetYear() == 2011);
		}
	}

	WHEN("Date will exceeded max value")
	{
		CDate date(1, Month::DECEMBER, 9999);
		THEN("Will be exception")
		{
			CHECK_THROWS_WITH(date + 100, "Date exceeded max date value");
		}
	}
}

TEST_CASE("Operator -")
{
	WHEN("Date - digit")
	{
		CDate date(12, Month::MARCH, 2011);
		CDate date1 = date - 400;
		THEN("Date will true")
		{
			CHECK(date1.GetDay() == 5);
			CHECK(date1.GetMonth() == Month::FEBRUARY);
			CHECK(date1.GetYear() == 2010);
		}
	}

	WHEN("Date will bellow min value")
	{
		CDate date(5, Month::MARCH, 1970);
		THEN("Will trow exception")
		{
			CHECK_THROWS_WITH(date - 200, "Date bellow min date value");
		}
	}

	WHEN("Date - date, first > second")
	{
		CDate date1(12, Month::MARCH, 2011);
		CDate date2(5, Month::FEBRUARY, 2010);
		THEN("Result = difference between dates")
		{
			CHECK((date1 - date2) == 400);
		}
	}

	WHEN("Date - date, first < second")
	{
		CDate date1(28, Month::OCTOBER, 2009);
		CDate date2(5, Month::FEBRUARY, 2010);
		THEN("Result = difference between dates")
		{
			CHECK((date1 - date2) == -100);
		}
	}
}

TEST_CASE("Operator +=")
{
	WHEN("Date += digit")
	{
		CDate date(5, Month::FEBRUARY, 2010);
		date += 400;
		THEN("Date will true")
		{
			CHECK(date.GetDay() == 12);
			CHECK(date.GetMonth() == Month::MARCH);
			CHECK(date.GetYear() == 2011);
		}
	}

	WHEN("Date will exceeded max value")
	{
		CDate date(1, Month::DECEMBER, 9999);
		THEN("Will be exception")
		{
			CHECK_THROWS_WITH(date += 100, "Date exceeded max date value");
		}
	}
}

TEST_CASE("Operator -=")
{
	WHEN("Date -= digit")
	{
		CDate date(12, Month::MARCH, 2011);
		date -= 400;
		THEN("Date will true")
		{
			CHECK(date.GetDay() == 5);
			CHECK(date.GetMonth() == Month::FEBRUARY);
			CHECK(date.GetYear() == 2010);
		}
	}

	WHEN("Date will bellow min value")
	{
		CDate date(5, Month::MARCH, 1970);
		THEN("Will trow exception")
		{
			CHECK_THROWS_WITH(date -= 200, "Date bellow min date value");
		}
	}
}

TEST_CASE("Operator <<")
{
	WHEN("Out << date")
	{
		std::ostringstream out;
		CDate date(18, Month::AUGUST, 2004);
		out << date;
		THEN("Date will write in format dd.mm.yyyy")
		{
			CHECK(out.str() == "18.08.2004");
		}
	}
}

TEST_CASE("Operator >>")
{
	WHEN("In >> date")
	{
		std::istringstream in("18.08.2004");
		CDate date;
		in >> date;
		THEN("Date will read and save to var")
		{
			CHECK(date.GetDay() == 18);
			CHECK(date.GetMonth() == Month::AUGUST);
			CHECK(date.GetYear() == 2004);
			CHECK(date.GetWeekDay() == WeekDay::WEDNESDAY);
		}
	}

	WHEN("Invalid format")
	{
		std::istringstream in("18,08/2004");
		CDate date;
		THEN("Will be exception")
		{
			CHECK_THROWS_WITH(in >> date, "Format must be dd.mm.yyyy, day <= 31, month <= 12, year 1970 - 9999");
		}
	}

	WHEN("Day more 31")
	{
		std::istringstream in("45.08.2004");
		CDate date;
		THEN("Will be exception")
		{
			CHECK_THROWS_WITH(in >> date, "Format must be dd.mm.yyyy, day <= 31, month <= 12, year 1970 - 9999");
		}
	}

	WHEN("Month more 12")
	{
		std::istringstream in("18.22.2004");
		CDate date;
		THEN("Will be exception")
		{
			CHECK_THROWS_WITH(in >> date, "Format must be dd.mm.yyyy, day <= 31, month <= 12, year 1970 - 9999");
		}
	}

	WHEN("Year bellow 1970")
	{
		std::istringstream in("18.08.1900");
		CDate date;
		THEN("Will be exception")
		{
			CHECK_THROWS_WITH(in >> date, "Format must be dd.mm.yyyy, day <= 31, month <= 12, year 1970 - 9999");
		}
	}

	WHEN("Year more 9999")
	{
		std::istringstream in("18.08.999999");
		CDate date;
		THEN("Will be exception")
		{
			CHECK_THROWS_WITH(in >> date, "Format must be dd.mm.yyyy, day <= 31, month <= 12, year 1970 - 9999");
		}
	}
}

TEST_CASE("Operators !=")
{
	WHEN("Date != date")
	{
		CDate date1;
		CDate date2(12);
		THEN("True")
		{
			CHECK(date1 != date2);
		}
	}

	WHEN("Date == date")
	{
		CDate date1(12);
		CDate date2(12);
		THEN("False")
		{
			CHECK(!(date1 != date2));
		}
	}
}

TEST_CASE("Operators =")
{
	WHEN("Date != date")
	{
		CDate date1;
		CDate date2(12);
		THEN("False")
		{
			CHECK(!(date1 == date2));
		}
	}

	WHEN("Date == date")
	{
		CDate date1(12);
		CDate date2(12);
		THEN("True")
		{
			CHECK(date1 == date2);
		}
	}
}

TEST_CASE("Operand <")
{
	WHEN("First < second")
	{
		CDate date1(12222);
		CDate date2(20000);
		THEN("True")
		{
			CHECK(date1 < date2);
		}
	}

	WHEN("First > second")
	{
		CDate date1(12222);
		CDate date2(20000);
		THEN("False")
		{
			CHECK(!(date2 < date1));
		}
	}

	WHEN("First = second")
	{
		CDate date1(20000);
		CDate date2(20000);
		THEN("False")
		{
			CHECK(!(date1 < date2));
		}
	}
}

TEST_CASE("Operand >")
{
	WHEN("First < second")
	{
		CDate date1(12222);
		CDate date2(20000);
		THEN("False")
		{
			CHECK(!(date1 > date2));
		}
	}

	WHEN("First > second")
	{
		CDate date1(12222);
		CDate date2(20000);
		THEN("True")
		{
			CHECK(date2 > date1);
		}
	}

	WHEN("First = second")
	{
		CDate date1(20000);
		CDate date2(20000);
		THEN("False")
		{
			CHECK(!(date1 < date2));
		}
	}
}

TEST_CASE("Operand <=")
{
	WHEN("First < second")
	{
		CDate date1(12222);
		CDate date2(20000);
		THEN("True")
		{
			CHECK(date1 <= date2);
		}
	}

	WHEN("First > second")
	{
		CDate date1(12222);
		CDate date2(20000);
		THEN("False")
		{
			CHECK(!(date2 <= date1));
		}
	}

	WHEN("First = second")
	{
		CDate date1(20000);
		CDate date2(20000);
		THEN("False")
		{
			CHECK(date1 <= date2);
		}
	}
}

TEST_CASE("Operand >=")
{
	WHEN("First < second")
	{
		CDate date1(12222);
		CDate date2(20000);
		THEN("False")
		{
			CHECK(!(date1 >= date2));
		}
	}

	WHEN("First > second")
	{
		CDate date1(12222);
		CDate date2(20000);
		THEN("true")
		{
			CHECK(date2 >= date1);
		}
	}

	WHEN("First = second")
	{
		CDate date1(20000);
		CDate date2(20000);
		THEN("False")
		{
			CHECK(date1 >= date2);
		}
	}
}
