#include "CCone.h"
#include <string>

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
	std::string bodyStr = CBody::ToString();
	bodyStr = bodyStr + "Base radius: " + std::to_string(m_baseRadius) + "\n";
	bodyStr = bodyStr + "Height: " + std::to_string(m_height) + "\n";
	return bodyStr;
}
