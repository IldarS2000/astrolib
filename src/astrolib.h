#ifndef ASTROLIB_H
#define ASTROLIB_H

#include "star.h"

namespace astrolib {

    double CelsiusToKelvin(double celsiusTemperature);
    double KelvinToCelsius(double kelvinTemperature);

    double Illumination(double lightFlow, double illuminatedSurfaceArea);

} // namespace astrolib

#endif // ASTROLIB_H
