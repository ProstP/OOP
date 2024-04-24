#include "ÑParallelepiped.h"
#include <string>

double ÑParallelepiped::GetWidth() const
{
	return m_width;
}

double ÑParallelepiped::GetHeight() const
{
	return m_height;
}

double ÑParallelepiped::GetDepth() const
{
	return m_depth;
}

std::string ÑParallelepiped::ToString() const
{
	std::string bodyStr = CBody::ToString();
	bodyStr = bodyStr + "Width: " + std::to_string(m_width) + "\n";
	bodyStr = bodyStr + "Height: " + std::to_string(m_height) + "\n";
	bodyStr = bodyStr + "Depth: " + std::to_string(m_depth) + "\n";
	return bodyStr;
}
