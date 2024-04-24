#pragma once
#include "CBody.h"
#include "PiNumber.h"

class CCone : CBody
{
public:
	CCone(double density, double baseRadius, double height)
		: CBody(density, (1 / 3) * Pi * baseRadius * baseRadius * height)
		, m_baseRadius{ baseRadius }
		, m_height{ height } {};
	double GetBaseRadius() const;
	double GetHeight() const;
	std::string ToString() const override;

private:
	double m_baseRadius;
	double m_height;
};
