#pragma once
#include <iostream>

class CBody
{
public:
	virtual double GetDensity() const;
	virtual double GetVolume() const;
	virtual double GetMass() const;
	virtual std::string ToString() const;
	virtual ~CBody() = default;
};
