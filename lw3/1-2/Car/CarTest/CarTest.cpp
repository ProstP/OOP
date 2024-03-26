#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../Car/Car.h"

SCENARIO("Turn on engine")
{
	WHEN("Turn on")
	{
		THEN("We will get true and engine will be on")
		{
			Car car;
			CHECK(!car.IsTurnedOn());
			CHECK(car.TurnOnEngine());
			CHECK(car.IsTurnedOn());
		}
	}
}

SCENARIO("Tests with usual data")
{
	WHEN("Put reverse gear from standing")
	{
		THEN("We will get true and gear == -1")
		{
			Car car;
			car.TurnOnEngine();
			CHECK(car.SetGear(-1));
			CHECK(car.GetGear() == -1);
		}
	}
	WHEN("Set max and min speed in reverse gear")
	{
		THEN("We will get true and max and min speed in reverse gear")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(-1);
			CHECK(car.SetSpeed(20));
			CHECK(car.GetSpeed() == 20);
			CHECK(car.SetSpeed(0));
			CHECK(car.GetSpeed() == 0);
		}
	}
	WHEN("Put 1 gear from standing")
	{
		THEN("We will get true and gear == 1")
		{
			Car car;
			car.TurnOnEngine();
			CHECK(car.SetGear(1));
			CHECK(car.GetGear() == 1);
		}
	}
	WHEN("Set max and min speed in 1 gear")
	{
		THEN("We will get true and max and min speed in 1 gear")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			CHECK(car.SetSpeed(30));
			CHECK(car.GetSpeed() == 30);
			CHECK(car.SetSpeed(0));
			CHECK(car.GetSpeed() == 0);
		}
	}
	WHEN("Put 2 gear")
	{
		THEN("We will get true and gear == 1")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(30);
			CHECK(car.SetGear(2));
			CHECK(car.GetGear() == 2);
		}
	}
	WHEN("Set max and min speed in 2 gear")
	{
		THEN("We will get true and max and min speed in 2 gear")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(30);
			car.SetGear(2);
			CHECK(car.SetSpeed(50));
			CHECK(car.GetSpeed() == 50);
			CHECK(car.SetSpeed(20));
			CHECK(car.GetSpeed() == 20);
		}
	}

	WHEN("Put 3 gear")
	{
		THEN("We will get true and gear == 1")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(30);
			CHECK(car.SetGear(3));
			CHECK(car.GetGear() == 3);
		}
	}
	WHEN("Set max and min speed in 3 gear")
	{
		THEN("We will get true and max and min speed in 3 gear")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(30);
			car.SetGear(3);
			CHECK(car.SetSpeed(60));
			CHECK(car.GetSpeed() == 60);
			CHECK(car.SetSpeed(30));
			CHECK(car.GetSpeed() == 30);
		}
	}
	WHEN("Put 4 gear")
	{
		THEN("We will get true and gear == 1")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(30);
			car.SetGear(3);
			car.SetSpeed(50);
			CHECK(car.SetGear(4));
			CHECK(car.GetGear() == 4);
		}
	}
	WHEN("Set max and min speed in 4 gear")
	{
		THEN("We will get true and max and min speed in 4 gear")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(30);
			car.SetGear(3);
			car.SetSpeed(60);
			car.SetGear(4);
			CHECK(car.SetSpeed(90));
			CHECK(car.GetSpeed() == 90);
			CHECK(car.SetSpeed(40));
			CHECK(car.GetSpeed() == 40);
		}
	}
	WHEN("Put 4 gear")
	{
		THEN("We will get true and gear == 1")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(30);
			car.SetGear(3);
			car.SetSpeed(50);
			CHECK(car.SetGear(5));
			CHECK(car.GetGear() == 5);
		}
	}
	WHEN("Set max and min speed in 4 gear")
	{
		THEN("We will get true and max and min speed in 4 gear")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(30);
			car.SetGear(3);
			car.SetSpeed(60);
			car.SetGear(5);
			CHECK(car.SetSpeed(150));
			CHECK(car.GetSpeed() == 150);
			CHECK(car.SetSpeed(50));
			CHECK(car.GetSpeed() == 50);
		}
	}
}

SCENARIO("Turn off engine")
{
	WHEN("Turn off with speed == 0")
	{
		THEN("We will get true and engine will be off")
		{
			Car car;
			CHECK(car.TurnOffEngine());
			CHECK(!car.IsTurnedOn());
		}
	}
	WHEN("Turn off with speed != 0")
	{
		THEN("We will get false and engine keep on")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(5);
			car.SetGear(0);
			CHECK(!car.TurnOffEngine());
			CHECK(car.IsTurnedOn());
		}
	}
	WHEN("Turn off with gear != 0")
	{
		THEN("We will get false and engine keep on")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			CHECK(!car.TurnOffEngine());
			CHECK(car.IsTurnedOn());
		}
	}
}

SCENARIO("Chenge direction in moving")
{
	WHEN("Move to forward")
	{
		THEN("Direction == Forward")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(5);
			CHECK(car.GetDirection() == CarDirection::Forward);
		}
	}
	WHEN("Move to forward in neutral gear")
	{
		THEN("Direction == Forward")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(5);
			car.SetGear(0);
			CHECK(car.GetDirection() == CarDirection::Forward);
		}
	}
	WHEN("Set speed = 0")
	{
		THEN("Direction == Standing")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(5);
			car.SetSpeed(0);
			CHECK(car.GetDirection() == CarDirection::Standing);
		}
	}
	WHEN("Move to backward")
	{
		THEN("Direction == Backward")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(-1);
			car.SetSpeed(5);
			CHECK(car.GetDirection() == CarDirection::Backward);
		}
	}
	WHEN("Move to backward in neutral gear")
	{
		THEN("Direction == Backward")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(-1);
			car.SetSpeed(5);
			car.SetGear(0);
			CHECK(car.GetDirection() == CarDirection::Backward);
		}
	}
}

SCENARIO("Set gear")
{
	WHEN("Engine off")
	{
		THEN("We will get false")
		{
			Car car;
			CHECK(!car.SetGear(1));
		}
	}
	WHEN("Gear less then min gear")
	{
		THEN("We will get false")
		{
			Car car;
			car.TurnOnEngine();
			CHECK(!car.SetGear(-5));
			CHECK(car.GetGear() == 0);
		}
	}
	WHEN("Gear more then max gear")
	{
		THEN("We will get false")
		{
			Car car;
			car.TurnOnEngine();
			CHECK(!car.SetGear(10));
			CHECK(car.GetGear() == 0);
		}
	}
	WHEN("Put reverse gear in forward gear")
	{
		THEN("We will get false and gear keep")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(5);
			CHECK(!car.SetGear(-1));
			CHECK(car.GetGear() == 1);
		}
	}
	WHEN("Put reverse gear in moving forward in neutral gear")
	{
		THEN("We will get false and gear keep")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(5);
			car.SetGear(0);
			CHECK(car.GetDirection() == CarDirection::Forward);
			CHECK(!car.SetGear(-1));
			CHECK(car.GetGear() == 0);
		}
	}
	WHEN("Put reverse gear when move backward in neutral gear")
	{
		THEN("We will get false and gear keep")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(-1);
			car.SetSpeed(10);
			car.SetGear(0);
			CHECK(car.GetDirection() == CarDirection::Backward);
			CHECK(!car.SetGear(-1));
			CHECK(car.GetGear() == 0);
		}
	}
	WHEN("Put forward gear from reverse with speed = 0")
	{
		THEN("Success gear will change")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(-1);
			CHECK(car.SetGear(1));
		}
	}
	WHEN("Put forward gear from reverse with speed != 0")
	{
		THEN("Gear can not be change")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(-1);
			car.SetSpeed(5);
			CHECK(!car.SetGear(1));
			CHECK(car.GetGear() == -1);
		}
	}
	WHEN("Put forward gear from neutral gear in moving backward")
	{
		THEN("Gear can not be change")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(-1);
			car.SetSpeed(5);
			car.SetGear(0);
			CHECK(car.GetDirection() == CarDirection::Backward);
			CHECK(!car.SetGear(1));
			CHECK(car.GetGear() == 0);
		}
	}
	WHEN("Speed is not in the right range")
	{
		THEN("We get false and speed not change")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(20);
			CHECK(!car.SetGear(5));
			CHECK(car.GetSpeed() == 20);
		}
	}
	WHEN("Put neutral gear from different gears and vice versa")
	{
		THEN("All true")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(20);
			CHECK(car.SetGear(0));
			car.SetGear(2);
			car.SetSpeed(30);
			CHECK(car.SetGear(0));
			car.SetGear(3);
			car.SetSpeed(40);
			CHECK(car.SetGear(0));
			car.SetGear(4);
			car.SetSpeed(50);
			CHECK(car.SetGear(0));
			car.SetGear(5);
			CHECK(car.SetGear(0));
			car.SetSpeed(0);
			car.SetGear(-1);
			car.SetSpeed(10);
			CHECK(car.SetGear(0));
		}
	}
}

SCENARIO("Set speed")
{
	WHEN("Engine off")
	{
		THEN("We get false and speed = 0")
		{
			Car car;
			CHECK(!car.SetSpeed(5));
			CHECK(car.GetSpeed() == 0);
		}
	}
	WHEN("Increase speed in neutral gear")
	{
		THEN("We get false and speed not change")
		{
			Car car;
			car.TurnOnEngine();
			CHECK(!car.SetSpeed(5));
			CHECK(car.GetSpeed() == 0);
		}
	}
	WHEN("Set speed more max value and less min value")
	{
		THEN("We get false and speed not change")
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(20);
			car.SetGear(2);
			CHECK(!car.SetSpeed(5));
			CHECK(!car.SetSpeed(60));
			CHECK(car.GetSpeed() == 20);
		}
	}
	WHEN("Decrease speed in neutral speed")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(0);
		CHECK(car.SetSpeed(5));
	}
}