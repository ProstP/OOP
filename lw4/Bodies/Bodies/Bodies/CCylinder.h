#pragma once
#include "CBody.h"
#include "PiNumber.h"

class CCylinder : public CBody
{
public:
	CCylinder(double density, double baseRadius, double height)
		: CBody(density, Pi * baseRadius * baseRadius * height)
		, m_baseRadius{ baseRadius }
		, m_height{ height } {};
	double GetBaseRadius() const;
	double GetHeight() const;
	std::string ToString() const override;
	~CCylinder() override = default;

private:
	double m_baseRadius;
	double m_height;
};
