#pragma once
#include "CSolidBody.h"

class CSphere : public CSolidBody
{
public:
	CSphere(double density, double radius)
		: CSolidBody(density)
		, m_radius{ radius } {};
	double GetVolume() const override;
	double GetRadius() const;
	std::string ToString() const override;
	~CSphere() override = default;

private:
	double m_radius;
};
