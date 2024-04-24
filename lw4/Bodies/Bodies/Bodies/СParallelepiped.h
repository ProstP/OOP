#pragma once
#include "CBody.h"

class ÑParallelepiped : public CBody
{
public:
	ÑParallelepiped(double density, double width, double height, double depth)
		: CBody(density, width * height * depth)
		, m_width{ width }
		, m_height{ height }
		, m_depth{ depth } {};
	double GetWidth() const;
	double GetHeight() const;
	double GetDepth() const;
	std::string ToString() const override;
	~ÑParallelepiped() override = default;

private:
	double m_width;
	double m_height;
	double m_depth;
};
