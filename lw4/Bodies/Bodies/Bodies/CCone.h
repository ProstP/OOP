#pragma once
#include "CBody.h"
#include "PiNumber.h"

class CCone : public CBody
{
public:
	CCone(double density, double baseRadius, double height)
		: CBody(density, Pi * baseRadius * baseRadius * height / 3)
		, m_baseRadius{ baseRadius }
		, m_height{ height } {};
	double GetBaseRadius() const;
	double GetHeight() const;
	std::string ToString() const override;
	~CCone() override = default;

private:
	double m_baseRadius;
	double m_height;
};
