#pragma once
#include "CSolidBody.h"

class CParallelepiped : public CSolidBody
{
public:
	CParallelepiped(double density, double width, double height, double depth)
		: CSolidBody(density)
		, m_width{ width }
		, m_height{ height }
		, m_depth{ depth } {};
	double GetVolume() const override;
	double GetWidth() const;
	double GetHeight() const;
	double GetDepth() const;
	std::string ToString() const override;
	~CParallelepiped() override = default;

private:
	double m_width;
	double m_height;
	double m_depth;
};
