#pragma once
#include "CBody.h"

class CSolidBody : public CBody
{
public:
	CSolidBody(double density);
	double GetDensity() const override;
	double GetMass() const override;
	virtual std::string ToString(const std::string& indent = "") const;
	virtual ~CSolidBody() = default;

private:
	double m_density;
};
