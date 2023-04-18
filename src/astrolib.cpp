#include "astrolib.h"
#include "constants.h"


double CelsiusToKelvin(const double celsiusTemperature)
{
    return celsiusTemperature - ABSOLUTE_ZERO_CELSIUS;
}

double KelvinToCelsius(const double kelvinTemperature)
{
    return kelvinTemperature + ABSOLUTE_ZERO_CELSIUS;
}

double Illumination(const double lightFlow, const double illuminatedSurfaceArea)
{
    return lightFlow / illuminatedSurfaceArea;
}