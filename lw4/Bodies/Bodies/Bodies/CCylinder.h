#pragma once
#include "CSolidBody.h"

class CCylinder : public CSolidBody
{
public:
	CCylinder(double density, double baseRadius, double height)
		: CSolidBody(density)
		, m_baseRadius{ baseRadius }
		, m_height{ height } {};
	double GetVolume() const override;
	double GetBaseRadius() const;
	double GetHeight() const;
	std::string ToString() const override;
	~CCylinder() override = default;

private:
	double m_baseRadius;
	double m_height;
};
