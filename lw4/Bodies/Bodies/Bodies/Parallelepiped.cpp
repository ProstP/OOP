#include "Parallelepiped.h"
#include <string>

double Parallelepiped::GetWidth() const
{
	return m_width;
}

double Parallelepiped::GetHeight() const
{
	return m_height;
}

double Parallelepiped::GetDepth() const
{
	return m_depth;
}

std::string Parallelepiped::ToString() const
{
	std::string bodyStr = CBody::ToString();
	bodyStr = bodyStr + "Width: " + std::to_string(m_width) + "\n";
	bodyStr = bodyStr + "Height: " + std::to_string(m_height) + "\n";
	bodyStr = bodyStr + "Depth: " + std::to_string(m_depth) + "\n";
	return bodyStr;
}
