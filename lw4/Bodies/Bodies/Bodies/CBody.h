#pragma once
#include <iostream>
#include <functional>

class CBody : public std::enable_shared_from_this<CBody>
{
public:
	virtual double GetDensity() const;
	virtual double GetVolume() const;
	virtual double GetMass() const;
	virtual std::string ToString(const std::string& indent = "") const;
	virtual void ExecuteFnToBodies(const std::function<void(const std::shared_ptr<CBody>&)>& fn) const;
	virtual ~CBody() = default;
};
