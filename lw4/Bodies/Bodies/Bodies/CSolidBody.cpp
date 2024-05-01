#include "CSolidBody.h"
#include <string>

CSolidBody::CSolidBody(double density)
    : m_density{ density }
{
    if (m_density < 1)
    {
        throw std::invalid_argument("The body parameters must be positive\n");
    }
}

double CSolidBody::GetDensity() const
{
    return m_density;
}

double CSolidBody::GetMass() const
{
    if (GetDensity() > DBL_MAX / GetVolume())
    {
        throw std::out_of_range("Mass exceeded acceptable value\n");
    }
    return GetDensity() * GetVolume();
}

std::string CSolidBody::ToString(const std::string& indent) const
{
    std::string bodyStr = indent + "Density: " + std::to_string(GetDensity()) + "\n";
    bodyStr = bodyStr + indent + "Volume: " + std::to_string(GetVolume()) + "\n";
    bodyStr = bodyStr + indent + "Mass: " + std::to_string(GetMass()) + "\n";
    return bodyStr;
}
