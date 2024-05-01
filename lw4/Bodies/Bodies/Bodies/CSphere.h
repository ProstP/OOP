#pragma once
#include "CSolidBody.h"

class CSphere : public CSolidBody
{
public:
	CSphere(double density, double radius);
	double GetVolume() const override;
	double GetRadius() const;
	std::string ToString(const std::string& indent = "") const override;
	~CSphere() override = default;

private:
	double m_radius;
};
