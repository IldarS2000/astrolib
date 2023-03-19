#include "astrolib.h"
#include "constants.h"

namespace astrolib {

    double CelsiusToKelvin(const double celsiusTemperature)
    {
        return celsiusTemperature - constants::ABSOLUTE_ZERO_CELSIUS;
    }

    double KelvinToCelsius(const double kelvinTemperature)
    {
        return kelvinTemperature + constants::ABSOLUTE_ZERO_CELSIUS;
    }

    double Illumination(const double lightFlow, const double illuminatedSurfaceArea)
    {
        return lightFlow / illuminatedSurfaceArea;
    }

} // namespace astrolib
