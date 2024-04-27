#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../Bodies/BodyStore.h"
#include "../Bodies/Data.h"
#include <string>

std::string SolidBodyInfo(double density, double volume, double mass)
{
	std::string densityStr = "Density: " + std::to_string(density) + "\n";
	std::string volumeStr = "Volume: " + std::to_string(volume) + "\n";
	std::string massStr = "Mass: " + std::to_string(mass) + "\n";

	return densityStr + volumeStr + massStr;
}

// Тест для compound компоненты не 0

TEST_CASE("Creating bodies")
{
	double density = 12;
	WHEN("Succes body creating with density and volume")
	{
		double volume = 5;
		double mass = density * volume;
		std::string bodyStr = SolidBodyInfo(density, volume, mass);
		CBody body(density, volume);
		THEN("Volume, density and mass are right")
		{
			CHECK(density == body.GetDensity());
			CHECK(volume == body.GetVolume());
			CHECK(mass == body.GetMass());
			CHECK(bodyStr == body.ToString());
		}
	}

	WHEN("Error density not positive")
	{
		auto fn = []()
		{
			CBody body(-1, 5);
		};
		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(fn(), "Density must be positive\n");
		}
	}

	WHEN("Error volume not positive")
	{
		auto fn = []()
		{
			CBody body(1, -5);
		};
		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(fn(), "Volume must be positive\n");
		}
	}

	WHEN("Succes creating sphere with density and radius")
	{
		double radius = 5;
		double volume = 4 * Pi * radius * radius * radius / 3;
		double mass = density * volume;
		std::string bodyStr = "\n<Sphere\n";
		bodyStr += SolidBodyInfo(density, volume, mass);
		bodyStr = bodyStr + "Radius: " + std::to_string(radius) + "\n";
		bodyStr += "/Sphere>\n\n";
		CSphere sphere(density, radius);
		THEN("Volume, density and mass are right")
		{
			CHECK(density == sphere.GetDensity());
			CHECK(volume == sphere.GetVolume());
			CHECK(mass == sphere.GetMass());
			CHECK(radius == sphere.GetRadius());
			CHECK(bodyStr == sphere.ToString());
		}
	}

	WHEN("Error radius not positive")
	{
		auto fn = []()
		{
			CSphere sphere(5, -1);
		};
		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(fn(), "Radius must be positive\n");
		}
	}

	WHEN("Succes creating parallelipiped with density, width, height and depth")
	{
		double width = 5;
		double height = 10;
		double depth = 7;
		double volume = width * height * depth;
		double mass = density * volume;
		std::string bodyStr = "\n<Parallelipiped\n";
		bodyStr += SolidBodyInfo(density, volume, mass);
		bodyStr = bodyStr + "Width: " + std::to_string(width) + "\n";
		bodyStr = bodyStr + "Height: " + std::to_string(height) + "\n";
		bodyStr = bodyStr + "Depth: " + std::to_string(depth) + "\n";
		bodyStr += "/Parallelipiped>\n\n";
		CParallelepiped parallelepiped(density, width, height, depth);
		THEN("Volume, density and mass are right")
		{
			CHECK(density == parallelepiped.GetDensity());
			CHECK(volume == parallelepiped.GetVolume());
			CHECK(mass == parallelepiped.GetMass());
			CHECK(width == parallelepiped.GetWidth());
			CHECK(height == parallelepiped.GetHeight());
			CHECK(depth == parallelepiped.GetDepth());
			CHECK(bodyStr == parallelepiped.ToString());
		}
	}

	WHEN("Error parallelipiped data not positive")
	{
		auto fn = []()
		{
			CParallelepiped parallelipiped(5, -1, - 5, 0);
		};
		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(fn(), "Data of parallelipiped must be positive\n");
		}
	}

	WHEN("Succes creating cylinder with density, base radius and height")
	{
		double baseRadius = 5;
		double height = 10;
		double volume = Pi * baseRadius * baseRadius * height;
		double mass = density * volume;
		std::string bodyStr = "\n<Cylinder\n";
		bodyStr += SolidBodyInfo(density, volume, mass);
		bodyStr = bodyStr + "Base radius: " + std::to_string(baseRadius) + "\n";
		bodyStr = bodyStr + "Height: " + std::to_string(height) + "\n";
		bodyStr += "/Cylinder>\n\n";
		CCylinder cylinder(density, baseRadius, height);
		THEN("Volume, density and mass are right")
		{
			CHECK(density == cylinder.GetDensity());
			CHECK(volume == cylinder.GetVolume());
			CHECK(mass == cylinder.GetMass());
			CHECK(baseRadius == cylinder.GetBaseRadius());
			CHECK(height == cylinder.GetHeight());
			CHECK(bodyStr == cylinder.ToString());
		}
	}

	WHEN("Error cylinder data not positive")
	{
		auto fn = []()
		{
			CCylinder cylinder(5, -1, -5);
		};
		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(fn(), "Data of cylinder must be positive\n");
		}
	}

	WHEN("Succes creating cone with density, base radius and height")
	{
		double baseRadius = 5;
		double height = 10;
		double volume = Pi * baseRadius * baseRadius * height / 3;
		double mass = density * volume;
		std::string bodyStr = "\n<Cone\n";
		bodyStr += SolidBodyInfo(density, volume, mass);
		bodyStr = bodyStr + "Base radius: " + std::to_string(baseRadius) + "\n";
		bodyStr = bodyStr + "Height: " + std::to_string(height) + "\n";
		bodyStr += "/Cone>\n\n";
		CCone cone(density, baseRadius, height);
		THEN("Volume, density and mass are right")
		{
			CHECK(density == cone.GetDensity());
			CHECK(volume == cone.GetVolume());
			CHECK(mass == cone.GetMass());
			CHECK(baseRadius == cone.GetBaseRadius());
			CHECK(height == cone.GetHeight());
			CHECK(bodyStr == cone.ToString());
		}
	}

	WHEN("Error cylinder data not positive")
	{
		auto fn = []()
		{
			CCone cone(5, -1, -5);
		};
		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(fn(), "Data of cone must be positive\n");
		}
	}

	WHEN("Success creating compound body with another bodies")
	{
		double radius = 5;
		double height = 10;
		double width = 15;
		double depth = 7;
		CSphere sphere(density, radius);
		CParallelepiped parallelepiped(density, width, height, depth);
		CCylinder cylinder(density, radius, height);
		CCone cone(density, radius, height);
		std::vector<std::shared_ptr<CBody>> bodies{ std::make_shared<CBody>(sphere), std::make_shared<CBody>(parallelepiped),
			std::make_shared<CBody>(cylinder), std::make_shared<CBody>(cone) };
		CCompound compound(bodies);
		double generalVolume = sphere.GetVolume() + parallelepiped.GetVolume() + cylinder.GetVolume() + cone.GetVolume();
		double generalMass = sphere.GetMass() + parallelepiped.GetMass() + cylinder.GetMass() + cone.GetMass();
		double generalDensity = generalMass / generalVolume;
		THEN("General volume, mass and densitity are right")
		{
			CHECK(generalVolume == compound.GetVolume());
			CHECK(generalMass == compound.GetMass());
			CHECK(generalDensity == compound.GetDensity());
		}
	}

	WHEN("Success creating compound body with another compound")
	{
		double radius = 5;
		double height = 10;
		CCone cone(density, radius, height);
		CCylinder cylinder(density, radius, height);
		std::vector<std::shared_ptr<CBody>> bodies1{ std::make_shared<CBody>(cone), std::make_shared<CBody>(cylinder) };
		CCompound com1(bodies1);
		std::vector<std::shared_ptr<CBody>> bodies2{ std::make_shared<CBody>(cone), std::make_shared<CBody>(com1) };
		CCompound com2(bodies2);
		double generalVolume = 2 * cone.GetVolume() + cylinder.GetVolume();
		double generalMass = 2 * cone.GetMass() + cylinder.GetMass();
		double generalDestinity = generalMass / generalVolume;
		THEN("General volume, mass and densitity are right")
		{
			CHECK(generalVolume == com2.GetVolume());
			CHECK(generalMass== com2.GetMass());
			CHECK(generalDestinity == com2.GetDensity());
		}
	}
}

TEST_CASE("Test store methods")
{
	BodyStore store;

	WHEN("Find body with max mass")
	{
		store.CreateParallelepiped(5, 5, 5, 5);
		store.CreateSphere(1, 5);
		store.CreateParallelepiped(2, 3, 3, 3);
		auto body = store.FindBodyWithMaxMass();
		CHECK(body->GetDensity() == 5);
		CHECK(body->GetVolume() == 125);
		CHECK(body->GetMass() == 625);
	}

	WHEN("Find lightest body in water")
	{
		store.CreateParallelepiped(1200, 500, 500, 500);
		store.CreateCylinder(800, 5, 5);
		store.CreateSphere(550, 2);
		auto body = store.FindLightestBodyInLiquid();
		CHECK(body->GetDensity() == 800);
	}
}
