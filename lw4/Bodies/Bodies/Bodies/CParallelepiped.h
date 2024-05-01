#pragma once
#include "CSolidBody.h"

class CParallelepiped : public CSolidBody
{
public:
	CParallelepiped(double density, double width, double height, double depth);
	double GetVolume() const override;
	double GetWidth() const;
	double GetHeight() const;
	double GetDepth() const;
	std::string ToString(const std::string& indent = "") const override;
	~CParallelepiped() override = default;

private:
	double m_width;
	double m_height;
	double m_depth;
};
