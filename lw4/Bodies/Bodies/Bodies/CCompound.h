#pragma once
#include "CBody.h"
#include <vector>

class CCompound : public CBody
{
public:
	CCompound(const std::vector<std::shared_ptr<CBody>>& bodies)
		: CBody(CCompound::CalculateGeneralDensity(bodies), CCompound::CalculateGeneralVolume(bodies))
		, m_bodies{ bodies } {};
	std::string ToString() const override;
	~CCompound() = default;

private:
	std::vector<std::shared_ptr<CBody>> m_bodies;
	double CalculateGeneralDensity(std::vector<std::shared_ptr<CBody>> bodies) const;
	double CalculateGeneralVolume(std::vector<std::shared_ptr<CBody>> bodies) const;
	double CalculateGeneralMass(std::vector<std::shared_ptr<CBody>> bodies) const;
};
