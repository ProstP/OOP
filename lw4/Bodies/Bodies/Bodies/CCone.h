#pragma once
#include "CSolidBody.h"

class CCone : public CSolidBody
{
public:
	CCone(double density, double baseRadius, double height)
		: CSolidBody(density)
		, m_baseRadius{ baseRadius }
		, m_height{ height } {};
	double GetVolume() const override;
	double GetBaseRadius() const;
	double GetHeight() const;
	std::string ToString() const override;
	~CCone() override = default;

private:
	double m_baseRadius;
	double m_height;
};
