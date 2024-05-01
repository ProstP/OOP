#pragma once
#include "CSolidBody.h"

class CCone : public CSolidBody
{
public:
	CCone(double density, double baseRadius, double height);
	double GetVolume() const override;
	double GetBaseRadius() const;
	double GetHeight() const;
	std::string ToString(const std::string& indent = "") const override;
	~CCone() override = default;

private:
	double m_baseRadius;
	double m_height;
};
