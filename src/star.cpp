#include <cmath>
#include "star.h"
#include "constants.h"

namespace astrolib {
    Star::Star()  = default;
    Star::~Star() = default;

    void Star::SetMass(const double mass)
    {
        this->mass = mass;
    }
    void Star::SetRadius(const double radius)
    {
        this->radius = radius;
    }
    void Star::SetPhotosphereTemperature(const double photosphereTemperature)
    {
        this->photosphereTemperature = photosphereTemperature;
    }

    double Star::GetMass() const
    {
        return this->mass;
    }
    double Star::GetRadius() const
    {
        return this->radius;
    }
    double Star::GetPhotosphereTemperature() const
    {
        return this->photosphereTemperature;
    }
    double Star::Luminosity() const
    {
        return 4 * constants::PI_NUMBER * std::pow(this->radius, 2) * constants::STEFAN_BOLTZMANN_CONSTANT *
               std::pow(this->photosphereTemperature, 4);
    }
} // namespace astrolib