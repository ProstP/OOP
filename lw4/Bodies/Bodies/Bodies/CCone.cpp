#include "CCone.h"
#include "Data.h"
#include <string>

double CCone::GetVolume() const
{
	if (m_baseRadius < 1 || m_height < 1)
	{
		throw std::invalid_argument("Data of cone must be positive\n");
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

std::string CCone::ToString() const
{
	std::string bodyStr = "\n<Cone\n";
	bodyStr += CBody::ToString();
	bodyStr = bodyStr + "Base radius: " + std::to_string(m_baseRadius) + "\n";
	bodyStr = bodyStr + "Height: " + std::to_string(m_height) + "\n";
	bodyStr += "/Cone>\n\n";
	return bodyStr;
}
