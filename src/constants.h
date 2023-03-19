#ifndef ASTROLIB_CONSTANTS_H
#define ASTROLIB_CONSTANTS_H

#include <cmath>
#include <cstdint>

namespace astrolib::constants {
    constexpr double PI_NUMBER       = 3.14159;
    constexpr double EULER_NUMBER    = 2.71828;
    constexpr int SPEED_OF_LIGHT_MPS = 299792458;

    constexpr double ABSOLUTE_ZERO_CELSIUS = -273.15;
    const double STEFAN_BOLTZMANN_CONSTANT = 5.6704 * (1 / std::pow(10, 8));
} // namespace astrolib::constants

#endif // ASTROLIB_CONSTANTS_H
