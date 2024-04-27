#include "CCylinder.h"
#include "Data.h"
#include <string>

double CCylinder::GetVolume() const
{
	if (m_baseRadius < 1 || m_height < 1)
	{
		throw std::invalid_argument("Data of cylinder must be positive\n");
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

std::string CCylinder::ToString() const
{
	std::string bodyStr = "\n<Cylinder\n";
	bodyStr += CBody::ToString();
	bodyStr = bodyStr + "Base radius: " + std::to_string(m_baseRadius) + "\n";
	bodyStr = bodyStr + "Height: " + std::to_string(m_height) + "\n";
	bodyStr += "/Cylinder>\n\n";
	return bodyStr;
}
