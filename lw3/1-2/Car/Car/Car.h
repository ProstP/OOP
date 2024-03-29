#pragma once
#include "CarDirection.h"

class Car
{
public:
	Car();
	[[nodiscard]] bool TurnOnEngine();
	[[nodiscard]] bool TurnOffEngine();
	[[nodiscard]] bool SetGear(int gear);
	[[nodiscard]] bool SetSpeed(int speed);
	bool IsTurnedOn();
	CarDirection GetDirection();
	int GetSpeed();
	int GetGear();
private:
	bool m_isTurnedOn;
	CarDirection m_direction;
	int m_speed;
	int m_gear;
};

