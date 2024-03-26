#pragma once
#include "CarDirection.h"

class Car
{
public:
	Car();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	[[nodiscard]] bool IsTurnedOn();
	[[nodiscard]] CarDirection GetDirection();
	[[nodiscard]] int GetSpeed();
	[[nodiscard]] int GetGear();
private:
	bool m_isTurnedOn;
	CarDirection m_direction;
	int m_speed;
	int m_gear;
};

