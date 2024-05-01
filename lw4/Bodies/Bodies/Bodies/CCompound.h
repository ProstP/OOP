#pragma once
#include "CSolidBody.h"
#include <vector>

class CCompound : public CBody
{
public:
	void AddChildSolidBody(std::shared_ptr<CSolidBody> body);
	void AddChildCompound(std::shared_ptr<CCompound> body);
	double GetVolume() const override;
	double GetMass() const override;
	double GetDensity() const override;
	std::string ToString(const std::string& indent = "") const override;
	void ExecuteFnToBodies(const std::function<void(const std::shared_ptr<CBody>&)>& fn) const override;
	~CCompound() = default;

private:
	std::vector<std::shared_ptr<CBody>> m_bodies;
};
