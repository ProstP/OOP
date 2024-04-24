#pragma once
#include <iostream>

class CBody
{
public:
	CBody(double density, double volume)
		: m_density{ density }
		, m_volume{ volume }
		, m_mass{ density * volume } {};
	double GetDensity() const;
	double GetVolume() const;
	double GetMass() const;
	virtual std::string ToString() const;
	virtual ~CBody() = default;

private:
	double m_density;
	double m_volume;
	double m_mass;
};
