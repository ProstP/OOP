#include "BodyStore.h"
#include "Data.h"

void BodyStore::CreateSphere(double density, double radius)
{
	CSphere sphere(density, radius);
	m_bodies.push_back(std::make_shared<CSphere>(sphere));
}

void BodyStore::CreateParallelepiped(double density, double width, double height, double depth)
{
	CParallelepiped parallelepiped(density, width, height, depth);
	m_bodies.push_back(std::make_shared<CParallelepiped>(parallelepiped));
}

void BodyStore::CreateCylinder(double density, double baseRadius, double height)
{
	CCylinder cylinder(density, baseRadius, height);
	m_bodies.push_back(std::make_shared<CCylinder>(cylinder));
}

void BodyStore::CreateCone(double density, double baseRadius, double height)
{
	CCone cone(density, baseRadius, height);
	m_bodies.push_back(std::make_shared<CCone>(cone));
}

void BodyStore::CreateCompound(const std::vector<std::shared_ptr<CBody>>& bodies)
{
	CCompound compound(bodies);
	m_bodies.push_back(std::make_shared<CCompound>(compound));
}

void BodyStore::ExecuteFnToAllBodies(const std::function<void(std::shared_ptr<CBody>)>& fn) const
{
	for (const auto& body : m_bodies)
	{
		fn(body);
	}
}

std::shared_ptr<CBody> BodyStore::FindBodyWithMaxMass() const
{
	double maxMass = 0;
	std::shared_ptr<CBody> bodyMaxMass;

	for (auto body : m_bodies)
	{
		if (body->GetMass() > maxMass)
		{
			maxMass = body->GetMass();
			bodyMaxMass = body;
		}
	}

	return bodyMaxMass;
}

std::shared_ptr<CBody> BodyStore::FindLightestBodyInLiquid() const
{
	double lightestValue = DBL_MAX;
	std::shared_ptr<CBody> lightestBody;

	for (auto body : m_bodies)
	{
		double value = (body->GetDensity() - waterDensity) * g * body->GetVolume();
		if (value < lightestValue)
		{
			lightestValue = value;
			lightestBody = body;
		}
	}

	return lightestBody;
}
