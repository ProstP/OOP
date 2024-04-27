#include "CParallelepiped.h"
#include <string>

double CParallelepiped::GetVolume() const
{
	if (m_width < 1 || m_height < 1 || m_depth< 1)
	{
		throw std::invalid_argument("Data of parallelipiped must be positive\n");
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

std::string CParallelepiped::ToString() const
{
	std::string bodyStr = "\n<Parallelipiped\n";
	bodyStr += CBody::ToString();
	bodyStr = bodyStr + "Width: " + std::to_string(m_width) + "\n";
	bodyStr = bodyStr + "Height: " + std::to_string(m_height) + "\n";
	bodyStr = bodyStr + "Depth: " + std::to_string(m_depth) + "\n";
	bodyStr += "/Parallelipiped>\n\n";
	return bodyStr;
}
