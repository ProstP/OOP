#include "CCompound.h"

double CCompound::CalculateGeneralDensity(std::vector<std::shared_ptr<CBody>> bodies) const
{
	return CalculateGeneralMass(bodies) / CalculateGeneralVolume(bodies);
}

//enable shared_ptr
//Проблема с зацикливанием, add добавить
//Вычитывать не сохранять

double CCompound::CalculateGeneralVolume(std::vector<std::shared_ptr<CBody>> bodies) const
{
	double volume = 0;

	for (auto body : bodies)
	{
		volume += body->GetVolume();
	}

	return volume;
}

double CCompound::CalculateGeneralMass(std::vector<std::shared_ptr<CBody>> bodies) const
{
	double mass = 0;

	for (auto body : bodies)
	{
		mass += body->GetMass();
	}

	return mass;
}

std::string CCompound::ToString() const
{
	std::string bodyStr = "\n<Compound\n";

	for (auto body : m_bodies)
	{
		bodyStr += body->ToString();
	}
	bodyStr += "/Compound>\n\n";

	return bodyStr;
}
