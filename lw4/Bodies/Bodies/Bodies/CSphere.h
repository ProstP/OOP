#pragma once
#include "CBody.h"
#include "PiNumber.h"

class CSphere : public CBody
{
public:
	CSphere(double density, double radius)
		: CBody(density, 4 * Pi * radius * radius * radius / 3)
		, m_radius{ radius } {};
	double GetRadius() const;
	std::string ToString() const override;
	~CSphere() override = default;

private:
	double m_radius;
};
