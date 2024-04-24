#pragma once
#include "CBody.h"
#include "PiNumber.h"

class CSphere : CBody
{
public:
	CSphere(double density, double radius)
		: CBody(density, (4 / 3) * Pi * radius * radius * radius)
		, m_radius{ radius } {};
	double GetRadius() const;
	std::string ToString() const override;

private:
	double m_radius;
};
