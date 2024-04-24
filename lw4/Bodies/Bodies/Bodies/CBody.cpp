#include "CBody.h"
#include <string>

double CBody::GetDensity() const
{
	return m_density;
}

double CBody::GetVolume() const
{
	return m_volume;
}

double CBody::GetMass() const
{
	return m_mass;
}

std::string CBody::ToString() const
{
	std::string density = "Density: " + std::to_string(m_density) + "\n";
	std::string volume = "Volume: " + std::to_string(m_volume) + "\n";
	std::string mass = "Mass: " + std::to_string(m_mass) + "\n";
	return std::string(density + volume + mass);
}
