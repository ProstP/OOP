#include "CarController.h"
#include "Car.h"
#include <iostream>
#include <map>

const int INFO = 0;
const int TURN_ON_ENGINE = 1;
const int TURN_OFF_ENGINE = 2;
const int SET_GEAR = 3;
const int SET_SPEED = 4;
const int EXIT = 5;

const std::map<int, std::string> COMMAND_KEYS{
	{ INFO, "Info" },
	{ TURN_ON_ENGINE, "Turn on engine" },
	{ TURN_OFF_ENGINE, "Turn of engine" },
	{ SET_GEAR, "Set gear" },
	{ SET_SPEED, "Set speed" },
	{ EXIT, "Exit" }
};

const std::map<CarDirection, std::string> DIRECTION_STRING{
	{ CarDirection::Backward, "Backward" },
	{ CarDirection::Forward, "Forward" },
	{ CarDirection::Standing, "Is staying" }
};

void PrintCommands()
{
	for (const auto& [key, command] : COMMAND_KEYS)
	{
		std::cout << "[" << key << "]: " << command << "\n";
	}
}

void Info(Car& car)
{
	std::cout << "Gear: " << car.GetGear() << "\n"
			  << "Speed: " << car.GetSpeed() << "\n"
			  << "Engine: " << (car.IsTurnedOn() ? "On" : "Off") << "\n"
			  << "Direction: " << DIRECTION_STRING.at(car.GetDirection()) << "\n";
}

void TurnOnEngine(Car& car)
{
	if (car.TurnOnEngine())
	{
		std::cout << "Engine on\n";
	}
	else
	{
		std::cout << "Engine can not be on\n";
	}
}

void TurnOffEngine(Car& car)
{
	if (car.TurnOffEngine())
	{
		std::cout << "Engine off\n";
	}
	else
	{
		std::cout << "Engine can not be off\n";
	}
}

void SetGear(Car& car)
{
	std::cout << "Set new gear:\n";
	int gear;
	std::cin >> gear;
	if (car.SetGear(gear))
	{
		std::cout << "Gear has been changed\n";
	}
	else
	{
		std::cout << "Gear can not be changed\n";
	}
}

void SetSpeed(Car& car)
{
	std::cout << "Set new speed:\n";
	int speed;
	std::cin >> speed;
	if (car.SetSpeed(speed))
	{
		std::cout << "Speed has been changed\n";
	}
	else
	{
		std::cout << "Speed can not be changed\n";
	}
}

void ActivateCar()
{
	int command;
	PrintCommands();
	Car car;
	while (std::cin >> command)
	{
		if (command == EXIT)
		{
			break;
		}
		switch (command)
		{
		case INFO:
			Info(car);
			break;
		case TURN_ON_ENGINE:
			TurnOnEngine(car);
			break;
		case TURN_OFF_ENGINE:
			TurnOffEngine(car);
			break;
		case SET_GEAR:
			SetGear(car);
			break;
		case SET_SPEED:
			SetSpeed(car);
			break;
		default:
			std::cout << "Unknown command\n";
			break;
		}

		PrintCommands();
	}
}
