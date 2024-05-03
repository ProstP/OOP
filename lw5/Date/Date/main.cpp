#include <iostream>
#include "CDate.h"

int main()
{
	unsigned day, month, year;
	char ch;
	std::cin >> day >> ch >> month >> ch >> year;
	std::cout << day << " " << month << " " << year << "\n";
	/*
	CDate date(31, Month::DECEMBER, 1976);
	CDate date1 = ++date;
	std::cout << (unsigned)date1.GetMonth() << " " << (unsigned)date.GetMonth();*/
}