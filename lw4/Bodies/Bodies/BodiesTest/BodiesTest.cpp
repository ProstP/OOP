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

TEST_CASE("Creating bodies")
{
	double density = 12;

	WHEN("Create sloid body with not positive density")
	{
		auto fn = []()
		{
			CSolidBody body(-1);
		};
		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(fn(), "The body parameters must be positive\n");
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

	WHEN("Mass exceeded max double value")
	{
		CSphere sphere(DBL_MAX, 500);
		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(sphere.GetMass(), "Mass exceeded acceptable value\n");
		}
	}

	WHEN("Volume exceeded max double value")
	{
		CSphere sphere(500, DBL_MAX);
		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(sphere.GetVolume(), "Volume exceeded acceptable value\n");
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
			CHECK_THROWS_WITH(fn(), "The body parameters must be positive\n");
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

	WHEN("Volume exceeded max double value")
	{
		CParallelepiped parallelepiped(500, DBL_MAX / 100, 6000, 2200);
		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(parallelepiped.GetVolume(), "Volume exceeded acceptable value\n");
		}
	}

	WHEN("Error parallelipiped parameters not positive")
	{
		auto fn = []()
		{
			CParallelepiped parallelipiped(5, -1, - 5, 0);
		};
		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(fn(), "The body parameters must be positive\n");
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

	WHEN("Volume exceeded max double value")
	{
		CCylinder cylinder(500, DBL_MAX / 100, 5000);
		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(cylinder.GetVolume(), "Volume exceeded acceptable value\n");
		}
	}

	WHEN("Error cylinder parameters not positive")
	{
		auto fn = []()
		{
			CCylinder cylinder(5, -1, -5);
		};
		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(fn(), "The body parameters must be positive\n");
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

	WHEN("Volume exceeded max double value")
	{
		CCone cone(500, DBL_MAX / 100, 5000);
		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(cone.GetVolume(), "Volume exceeded acceptable value\n");
		}
	}

	WHEN("Error cone parameters not positive")
	{
		auto fn = []()
		{
			CCone cone(5, -1, -5);
		};
		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(fn(), "The body parameters must be positive\n");
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
		CCompound compound;
		std::shared_ptr<CCompound> ptr = std::make_shared<CCompound>(compound);
		ptr->AddChildSolidBody(std::make_shared<CSphere>(sphere));
		ptr->AddChildSolidBody(std::make_shared<CParallelepiped>(parallelepiped));
		ptr->AddChildSolidBody(std::make_shared<CCylinder>(cylinder));
		ptr->AddChildSolidBody(std::make_shared<CCone>(cone));
		double generalVolume = sphere.GetVolume() + parallelepiped.GetVolume() + cylinder.GetVolume() + cone.GetVolume();
		double generalMass = sphere.GetMass() + parallelepiped.GetMass() + cylinder.GetMass() + cone.GetMass();
		double generalDensity = generalMass / generalVolume;
		THEN("General volume, mass and densitity are right")
		{
			CHECK(generalVolume == ptr->GetVolume());
			CHECK(generalMass == ptr->GetMass());
			CHECK(generalDensity == ptr->GetDensity());
		}
	}

	WHEN("Success creating compound body with another compound")
	{
		double radius = 5;
		double height = 10;
		CCone cone(density, radius, height);
		CCylinder cylinder(density, radius, height);;
		CCompound com1;
		std::shared_ptr<CCompound> ptr1 = std::make_shared<CCompound>(com1);
		ptr1->AddChildSolidBody(std::make_shared<CCone>(cone));
		ptr1->AddChildSolidBody(std::make_shared<CCylinder>(cylinder));
		CCompound com2;
		std::shared_ptr<CCompound> ptr2 = std::make_shared<CCompound>(com2);
		ptr2->AddChildSolidBody(std::make_shared<CCone>(cone));
		ptr2->AddChildCompound(ptr1);
		double generalVolume = 2 * cone.GetVolume() + cylinder.GetVolume();
		double generalMass = 2 * cone.GetMass() + cylinder.GetMass();
		double generalDestinity = generalMass / generalVolume;
		std::string bodyStr1 = "\n<Compound\n";
		std::string densityStr1 = "Density: " + std::to_string(ptr2->GetDensity()) + "\n";
		std::string volumeStr1 = "Volume: " + std::to_string(ptr2->GetVolume()) + "\n";
		std::string massStr1 = "Mass: " + std::to_string(ptr2->GetMass()) + "\n";
		std::string coneStr1 = cone.ToString("    ");
		std::string bodyStr2 = "\n    <Compound\n";
		std::string densityStr2 = "    Density: " + std::to_string(ptr1->GetDensity()) + "\n";
		std::string volumeStr2 = "    Volume: " + std::to_string(ptr1->GetVolume()) + "\n";
		std::string massStr2 = "    Mass: " + std::to_string(ptr1->GetMass()) + "\n";
		std::string coneStr2 = cone.ToString("        ");
		std::string cylinderStr = cylinder.ToString("        ");
		std::string bodyStr3 = "    /Compound>\n\n";
		std::string bodyStr4 = "/Compound>\n\n";
		std::string bodyStr = bodyStr1 + densityStr1 + volumeStr1 + massStr1 + coneStr1 + 
			bodyStr2 + densityStr2 + volumeStr2 + massStr2 + coneStr2 + cylinderStr + bodyStr3 + bodyStr4;
		THEN("General volume, mass and densitity are right")
		{
			CHECK(generalVolume == ptr2->GetVolume());
			CHECK(generalMass== ptr2->GetMass());
			CHECK(generalDestinity == ptr2->GetDensity());
			CHECK(bodyStr == ptr2->ToString());
		}
	}

	WHEN("Compound add self")
	{
		CCompound com;
		std::shared_ptr<CCompound> ptr = std::make_shared<CCompound>(com);
		THEN("Will trow exception")
		{
			CHECK_THROWS_WITH(ptr->AddChildCompound(ptr), "Compound body can't has self in bodies\n");
		}
	}

	WHEN("Cyclic add")
	{
		CCompound compound;
		std::shared_ptr<CCompound> ptr1 = std::make_shared<CCompound>(compound);
		std::shared_ptr<CCompound> ptr2 = std::make_shared<CCompound>(compound);
		std::shared_ptr<CCompound> ptr3 = std::make_shared<CCompound>(compound);

		ptr2->AddChildCompound(ptr3);
		ptr1->AddChildCompound(ptr2);

		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(ptr3->AddChildCompound(ptr1), "Compound body can't has self in bodies\n");
		}
	}

	WHEN("Compound don't has bodies")
	{
		CCompound compound;
		std::shared_ptr<CCompound> ptr = std::make_shared<CCompound>(compound);
		THEN("Density, volume and mass = 0")
		{
			CHECK(ptr->GetDensity() == 0);
			CHECK(ptr->GetVolume() == 0);
			CHECK(ptr->GetMass() == 0);
		}
	}

	WHEN("Sum volume excedeed max double value")
	{
		CParallelepiped body(500, DBL_MAX / 10, 2, 2);
		CCompound compound;
		std::shared_ptr<CCompound> ptr = std::make_shared<CCompound>(compound);
		ptr->AddChildSolidBody(std::make_shared<CParallelepiped>(body));
		ptr->AddChildSolidBody(std::make_shared<CParallelepiped>(body));
		ptr->AddChildSolidBody(std::make_shared<CParallelepiped>(body));
		THEN("Will trow exception")
		{
			CHECK_THROWS_WITH(ptr->GetVolume(), "Volume exceeded acceptable value\n");
		}
	}

	WHEN("Sum mass excedeed max double value")
	{
		CParallelepiped body(DBL_MAX / 3, 10, 2, 2);
		CCompound compound;
		std::shared_ptr<CCompound> ptr = std::make_shared<CCompound>(compound);
		ptr->AddChildSolidBody(std::make_shared<CParallelepiped>(body));
		ptr->AddChildSolidBody(std::make_shared<CParallelepiped>(body));
		ptr->AddChildSolidBody(std::make_shared<CParallelepiped>(body));
		ptr->AddChildSolidBody(std::make_shared<CParallelepiped>(body));
		THEN("Will trow exception")
		{
			CHECK_THROWS_WITH(ptr->GetMass(), "Mass exceeded acceptable value\n");
		}
	}
}

TEST_CASE("Test store methods")
{
	BodyStore store;

	WHEN("Get all bodies in string with fn")
	{
		store.CreateCone(5, 5, 5);
		CCone cone(5, 5, 5);
		store.CreateSphere(5, 2);
		CSphere sphere(5, 2);
		auto ptr = store.CreateCompound();
		CCone cone1(5, 2, 5);
		ptr->AddChildSolidBody(std::make_shared<CCone>(cone1));
		std::string str = cone.ToString() + sphere.ToString() + ptr->ToString();
		std::string result;
		auto fn = []
		THEN("Str will contain info about bodies")
		{
			CHECK(str == store.);
		}
	}

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
