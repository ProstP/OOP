#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../Bodies/CBody.h"
#include "../Bodies/CSphere.h"
#include "../Bodies/СParallelepiped.h"
#include "../Bodies/CCylinder.h"
#include "../Bodies/CCone.h"
#include <string>
#include "../Bodies/PiNumber.h"

std::string SolidBodyInfo(double density, double volume, double mass)
{
	std::string densityStr = "Density: " + std::to_string(density) + "\n";
	std::string volumeStr = "Volume: " + std::to_string(volume) + "\n";
	std::string massStr = "Mass: " + std::to_string(mass) + "\n";

	return densityStr + volumeStr + massStr;
}

TEST_CASE("Creating bodies")
{
	double density = 12;
	WHEN("Succes body creating with density and volume")
	{
		double volume = 5;
		double mass = density * volume;
		std::string bodyStr = SolidBodyInfo(density, volume, mass);
		CBody body(density, volume);
		THEN("Volume, density and mass is right")
		{
			CHECK(density == body.GetDensity());
			CHECK(volume == body.GetVolume());
			CHECK(mass == body.GetMass());
			CHECK(bodyStr == body.ToString());
		}
	}

	WHEN("Succes creating sphere with density and radius")
	{
		double radius = 5;
		double volume = 4 * Pi * radius * radius * radius / 3;
		double mass = density * volume;
		std::string bodyStr = SolidBodyInfo(density, volume, mass);
		bodyStr = bodyStr + "Radius: " + std::to_string(radius) + "\n";
		CSphere sphere(density, radius);
		THEN("Volume, density and mass is right")
		{
			CHECK(density == sphere.GetDensity());
			CHECK(volume == sphere.GetVolume());
			CHECK(mass == sphere.GetMass());
			CHECK(radius == sphere.GetRadius());
			CHECK(bodyStr == sphere.ToString());
		}
	}

	WHEN("Succes creating sphere with density, width, height and depth")
	{
		double width = 5;
		double height = 10;
		double depth = 7;
		double volume = width * height * depth;
		double mass = density * volume;
		std::string bodyStr = SolidBodyInfo(density, volume, mass);
		bodyStr = bodyStr + "Width: " + std::to_string(width) + "\n";
		bodyStr = bodyStr + "Height: " + std::to_string(height) + "\n";
		bodyStr = bodyStr + "Depth: " + std::to_string(depth) + "\n";
		СParallelepiped parallelepiped(density, width, height, depth);
		THEN("Volume, density and mass is right")
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

	WHEN("Succes creating cylinder with density, base radius and height")
	{
		double baseRadius = 5;
		double height = 10;
		double volume = Pi * baseRadius * baseRadius * height;
		double mass = density * volume;
		std::string bodyStr = SolidBodyInfo(density, volume, mass);
		bodyStr = bodyStr + "Base radius: " + std::to_string(baseRadius) + "\n";
		bodyStr = bodyStr + "Height: " + std::to_string(height) + "\n";
		CCylinder cylinder(density, baseRadius, height);
		THEN("Volume, density and mass is right")
		{
			CHECK(density == cylinder.GetDensity());
			CHECK(volume == cylinder.GetVolume());
			CHECK(mass == cylinder.GetMass());
			CHECK(baseRadius == cylinder.GetBaseRadius());
			CHECK(height == cylinder.GetHeight());
			CHECK(bodyStr == cylinder.ToString());
		}
	}

	WHEN("Succes creating cone with density, base radius and height")
	{
		double baseRadius = 5;
		double height = 10;
		double volume = Pi * baseRadius * baseRadius * height / 3;
		double mass = density * volume;
		std::string bodyStr = SolidBodyInfo(density, volume, mass);
		bodyStr = bodyStr + "Base radius: " + std::to_string(baseRadius) + "\n";
		bodyStr = bodyStr + "Height: " + std::to_string(height) + "\n";
		CCone cone(density, baseRadius, height);
		THEN("Volume, density and mass is right")
		{
			CHECK(density == cone.GetDensity());
			CHECK(volume == cone.GetVolume());
			CHECK(mass == cone.GetMass());
			CHECK(baseRadius == cone.GetBaseRadius());
			CHECK(height == cone.GetHeight());
			CHECK(bodyStr == cone.ToString());
		}
	}
}
