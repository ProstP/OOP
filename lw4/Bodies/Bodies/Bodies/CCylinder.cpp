#include "CCylinder.h"
#include <string>

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
	std::string bodyStr = CBody::ToString();
	bodyStr = bodyStr + "Base radius: " + std::to_string(m_baseRadius) + "\n";
	bodyStr = bodyStr + "Height: " + std::to_string(m_height) + "\n";
	return bodyStr;
}
