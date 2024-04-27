#pragma once
#include "CSphere.h"
#include "CParallelepiped.h"
#include "CCylinder.h"
#include "CCone.h"
#include "CCompound.h"
#include <functional>
#include <vector>

class BodyStore
{
public:
	void CreateSphere(double density, double radius);
	void CreateParallelepiped(double density, double width, double height, double depth);
	void CreateCylinder(double density, double baseRadius, double height);
	void CreateCone(double density, double baseRadius, double height);
	void CreateCompound(const std::vector<std::shared_ptr<CBody>>& bodies);
	void ExecuteFnToAllBodies(const std::function<void(std::shared_ptr<CBody>)>& fn) const;
	std::shared_ptr<CBody> FindBodyWithMaxMass() const;
	std::shared_ptr<CBody> FindLightestBodyInLiquid() const;

private:
	std::vector<std::shared_ptr<CBody>> m_bodies;
};

