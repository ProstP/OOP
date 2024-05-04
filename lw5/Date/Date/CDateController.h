#pragma once
#include "CDate.h"
#include <iostream>
#include <vector>

class CDateController
{
public:
	void Handle(std::istream& in, std::ostream& out);

private:
	std::vector<std::shared_ptr<CDate>> m_dates;
	void PrintCommands(std::ostream& out) const;
	bool DefineCommand(unsigned command, std::istream& in, std::ostream& out);
	void PrintAllBodies(std::ostream& out) const;
	void CreateDateWithDDMMYYYY(std::istream& in);
	void CreateDateWithTimeStamp(std::istream& in);
	void CalculateSumDateAndValue(std::istream& in, std::ostream& out) const;
	void IncreaseDate(std::istream& in);
	void IncreaseDateToValue(std::istream& in);
	void CalculateSubDates(std::istream& in, std::ostream& out) const;
	void CalculateSubDateAndValue(std::istream& in, std::ostream& out) const;
	void DecreaseDate(std::istream& in);
	void DecreaseDateToValue(std::istream& in);
	void CompareDatesToEqual(std::istream& in, std::ostream& out) const;
	void CompareDatesToStrictInequal(std::istream& in, std::ostream& out) const;
	void CompareDatesToNonStrictInequal(std::istream& in, std::ostream& out) const;
};
