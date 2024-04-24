#pragma once
#include "CBody.h"
#include "PiNumber.h"

class CCylinder : CBody
{
	CCylinder(double density, double baseRadius, double height)
		: CBody(density, Pi * baseRadius * baseRadius * height)
		, m_baseRadius{ baseRadius }
		, m_height{ height } {};
	double GetBaseRadius() const;
	double GetHeight() const;
	std::string ToString() const override;

private:
	double m_baseRadius;
	double m_height;
};
