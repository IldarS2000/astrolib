#include "astrolib.h"
#include "constants.h"

namespace astrolib {

    double CelsiusToKelvin(const double celsiusTemperature)
    {
        return celsiusTemperature - ABSOLUTE_ZERO_CELSIUS;
    }

    double KelvinToCelsius(const double kelvinTemperature)
    {
        return kelvinTemperature + ABSOLUTE_ZERO_CELSIUS;
    }

} // namespace astrolib
