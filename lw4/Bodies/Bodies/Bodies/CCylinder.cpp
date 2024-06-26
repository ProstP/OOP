#include "CCylinder.h"
#include "Data.h"
#include <string>

CCylinder::CCylinder(double density, double baseRadius, double height)
	: CSolidBody(density)
	, m_baseRadius{ baseRadius }
	, m_height{ height }
{
	if (m_baseRadius < 1 || m_height < 1)
	{
		throw std::invalid_argument("The body parameters must be positive\n");
	}
}

double CCylinder::GetVolume() const
{
	if (m_baseRadius > DBL_MAX / Pi / m_baseRadius / m_height)
	{
		throw std::out_of_range("Volume exceeded acceptable value\n");
	}
	return Pi * m_baseRadius * m_baseRadius * m_height;
}

double CCylinder::GetBaseRadius() const
{
	return m_baseRadius;
}

double CCylinder::GetHeight() const
{
	return m_height;
}

std::string CCylinder::ToString(const std::string& indent) const
{
	std::string bodyStr = "\n" + indent + "<Cylinder\n";
	bodyStr += CSolidBody::ToString(indent);
	bodyStr = bodyStr + indent + "Base radius: " + std::to_string(m_baseRadius) + "\n";
	bodyStr = bodyStr + indent + "Height: " + std::to_string(m_height) + "\n";
	bodyStr = bodyStr + indent + "/Cylinder>\n\n";
	return bodyStr;
}
