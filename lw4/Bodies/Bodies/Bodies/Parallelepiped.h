#pragma once
#include "CBody.h"

class Parallelepiped : CBody
{
public:
	Parallelepiped(double density, double width, double height, double depth)
		: CBody(density, width * height * depth)
		, m_width{ width }
		, m_height{ height }
		, m_depth{ depth } {};
	double GetWidth() const;
	double GetHeight() const;
	double GetDepth() const;
	std::string ToString() const override;

private:
	double m_width;
	double m_height;
	double m_depth;
};
