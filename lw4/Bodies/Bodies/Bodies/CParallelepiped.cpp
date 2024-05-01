#include "CParallelepiped.h"
#include <string>

CParallelepiped::CParallelepiped(double density, double width, double height, double depth)
	: CSolidBody(density)
	, m_width{ width }
	, m_height{ height }
	, m_depth{ depth }
{
	if (m_width < 1 || m_height < 1 || m_depth < 1)
	{
		throw std::invalid_argument("The body parameters must be positive\n");
	}
}

double CParallelepiped::GetVolume() const
{
	if (m_width > DBL_MAX / m_height / m_depth)
	{
		throw std::out_of_range("Volume exceeded acceptable value\n");
	}
	return m_width * m_height * m_depth;
}

double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

double CParallelepiped::GetDepth() const
{
	return m_depth;
}

std::string CParallelepiped::ToString(const std::string& indent) const
{
	std::string bodyStr = "\n" + indent + "<Parallelipiped\n";
	bodyStr += CSolidBody::ToString(indent);
	bodyStr = bodyStr + indent + "Width: " + std::to_string(m_width) + "\n";
	bodyStr = bodyStr + indent + "Height: " + std::to_string(m_height) + "\n";
	bodyStr = bodyStr + indent + "Depth: " + std::to_string(m_depth) + "\n";
	bodyStr = bodyStr + indent + "/Parallelipiped>\n\n";
	return bodyStr;
}
