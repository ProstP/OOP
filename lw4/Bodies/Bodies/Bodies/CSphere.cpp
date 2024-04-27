#include "CSphere.h"
#include <string>
#include "Data.h"

double CSphere::GetVolume() const
{
	if (m_radius < 1)
	{
		throw std::invalid_argument("Radius must be positive\n");
	}
	return 4 * Pi * m_radius * m_radius * m_radius / 3;
}

double CSphere::GetRadius() const
{
	return m_radius;
}

std::string CSphere::ToString() const
{
	std::string bodyStr = "\n<Sphere\n";
	bodyStr += CBody::ToString();
	bodyStr = bodyStr + "Radius: " + std::to_string(m_radius) + "\n";
	bodyStr += "/Sphere>\n\n";
	return bodyStr;
}
