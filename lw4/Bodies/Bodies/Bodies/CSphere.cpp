#include "CSphere.h"
#include <string>
#include "Data.h"

CSphere::CSphere(double density, double radius)
	: CSolidBody(density)
	, m_radius{ radius }
{
	if (m_radius < 1)
	{
		throw std::invalid_argument("The body parameters must be positive\n");
	}
}

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

std::string CSphere::ToString(const std::string& indent) const
{
	std::string bodyStr = "\n" + indent + "<Sphere\n";
	bodyStr += CSolidBody::ToString(indent);
	bodyStr = bodyStr + indent + "Radius: " + std::to_string(m_radius) + "\n";
	bodyStr = bodyStr + indent + "/Sphere>\n\n";
	return bodyStr;
}
