#include "CCompound.h"
#include <string>

void CCompound::AddChildSolidBody(std::shared_ptr<CSolidBody> body)
{
	m_bodies.push_back(body);
}

void CCompound::AddChildCompound(std::shared_ptr<CCompound> body)
{
	auto ptr = shared_from_this();
	auto fn = [&ptr](const std::shared_ptr<CBody>& body)
	{
		if (body == ptr)
		{
			throw std::invalid_argument("Compound body can't has self in bodies\n");
		}
	};
	fn(body);

	body->ExecuteFnToBodies(fn);
	m_bodies.push_back(body);
}

double CCompound::GetVolume() const
{
	double value = 0;

	for (const auto& body : m_bodies)
	{
		if (value > DBL_MAX - body->GetVolume())
		{
			throw std::out_of_range("Volume exceeded acceptable value\n");
		}
		value += body->GetVolume();
	}

	return value;
}

double CCompound::GetMass() const
{
	double value = 0;

	for (const auto& body : m_bodies)
	{
		if (value > DBL_MAX - body->GetMass())
		{
			throw std::out_of_range("Mass exceeded acceptable value\n");
		}
		value += body->GetMass();
	}

	return value;
}

double CCompound::GetDensity() const
{
	if (GetVolume() == 0)
	{
		return 0;
	}

	return GetMass() / GetVolume();
}

std::string CCompound::ToString(const std::string& indent) const
{
	std::string bodyStr = "\n" + indent + "<Compound\n";
	bodyStr = bodyStr + indent + "Density: " + std::to_string(GetDensity()) + "\n";
	bodyStr = bodyStr + indent + "Volume: " + std::to_string(GetVolume()) + "\n";
	bodyStr = bodyStr + indent + "Mass: " + std::to_string(GetMass()) + "\n";

	for (auto body : m_bodies)
	{
		bodyStr += body->ToString(indent + "    ");
	}
	bodyStr = bodyStr + indent + "/Compound>\n\n";

	return bodyStr;
}

void CCompound::ExecuteFnToBodies(const std::function<void(const std::shared_ptr<CBody>&)>& fn) const
{
	for (const auto& body : m_bodies)
	{
		fn(body);
		body->ExecuteFnToBodies(fn);
	}
}
