#pragma once
#include "CBody.h"

class CSolidBody : public CBody
{
public:
	CSolidBody(double density)
		: m_density{ density } {};
	double GetDensity() const override;
	double GetMass() const override;

private:
	double m_density;
};
