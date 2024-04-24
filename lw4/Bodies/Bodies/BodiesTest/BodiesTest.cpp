#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../Bodies/CBody.h"
#include <string>

TEST_CASE("Creating bodies")
{
	WHEN("Succes creating with density and volume")
	{
		double density = 12;
		double volume = 5;
		double mass = density * volume;
		std::string densityStr = "Density: " + std::to_string(density) + "\n";
		std::string volumeStr = "Volume: " + std::to_string(volume) + "\n";
		std::string massStr = "Mass: " + std::to_string(mass) + "\n";
		std::string bodyStr = densityStr + volumeStr + massStr;
		CBody body(density, volume);
		THEN("Volume, density and mass is right")
		{
			CHECK(density == body.GetDensity());
			CHECK(volume == body.GetVolume());
			CHECK(mass == body.GetMass());
			CHECK(bodyStr == body.ToString());
		}
	}
}
