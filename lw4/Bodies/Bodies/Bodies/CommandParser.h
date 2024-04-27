#pragma once
#include "BodyStore.h"
#include <iostream>

class CommandParser
{
public:
	CommandParser(BodyStore& store)
		: m_store{ store } {};
	void Handle(std::istream& in, std::ostream& out);

private:
	BodyStore m_store;
	void PrintCreateCommands(std::ostream& out) const;
	void DefineCreateCommands(int command, std::istream& in);
	void CreateSphere(std::istream& in);
	void CreateParallelepiped(std::istream& in);
	void CreateCylinder(std::istream& in);
	void CreateCone(std::istream& in);
	void CreateCompound(std::istream& in);
	void PrintCommands(std::ostream& out) const;
	void DefineCommands(int command, std::ostream& out) const;
	void PrintAllBodies(std::ostream& out) const;
	void PrintBodyWithMaxMass(std::ostream& out) const;
	void PrintLightestBodyInLiquid(std::ostream& out) const;
	std::vector<std::shared_ptr<CBody>> CreateBodiesForCompound(std::istream& in);
	std::shared_ptr<CSphere> CreateSphereForCompound(std::istream& in);
	std::shared_ptr<CParallelepiped> CreateParallelepipedForCompound(std::istream& in);
	std::shared_ptr<CCylinder> CreateCylinderForCompound(std::istream& in);
	std::shared_ptr<CCone> CreateConeForCompound(std::istream& in);
	std::shared_ptr<CCompound> CreateCompoundForCompound(std::istream& in);
};
