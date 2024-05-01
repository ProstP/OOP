#include "CCone.h"
#include "Data.h"
#include <string>

CCone::CCone(double density, double baseRadius, double height)
	: CSolidBody(density)
	, m_baseRadius{ baseRadius }
	, m_height{ height }
{
	if (m_baseRadius < 1 || m_height < 1)
	{
		throw std::invalid_argument("The body parameters must be positive\n");
	}
}

double CCone::GetVolume() const
{
	if (m_baseRadius > DBL_MAX / m_baseRadius / m_height * 3)
	{
		throw std::out_of_range("Volume exceeded acceptable value\n");
	}
	return Pi * m_baseRadius * m_baseRadius * m_height / 3;
}

double CCone::GetBaseRadius() const
{
	return m_baseRadius;
}

double CCone::GetHeight() const
{
	return m_height;
}

std::string CCone::ToString(const std::string& indent) const
{
	std::string bodyStr = "\n" + indent + "<Cone\n";
	bodyStr += CSolidBody::ToString(indent);
	bodyStr = bodyStr + indent + "Base radius: " + std::to_string(m_baseRadius) + "\n";
	bodyStr = bodyStr + indent + "Height: " + std::to_string(m_height) + "\n";
	bodyStr = bodyStr + indent + "/Cone>\n\n";
	return bodyStr;
}
