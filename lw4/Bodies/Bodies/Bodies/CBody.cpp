#include "CBody.h"

double CBody::GetDensity() const
{
	return 0.0;
}

double CBody::GetVolume() const
{
	return 0.0;
}

double CBody::GetMass() const
{
	return 0.0;
}

std::string CBody::ToString(const std::string& indent) const
{
	return std::string();
}

void CBody::ExecuteFnToBodies(const std::function<void(const std::shared_ptr<CBody>&)>& fn) const
{
	return;
}
