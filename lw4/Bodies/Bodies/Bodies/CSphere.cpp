#include "CSphere.h"
#include <string>

double CSphere::GetRadius() const
{
	return m_radius;
}

std::string CSphere::ToString() const
{
	std::string bodyStr = CBody::ToString();
	bodyStr = bodyStr + "Radius: " + std::to_string(m_radius) + "\n";
	return bodyStr;
}
