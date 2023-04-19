#ifndef ASTROLIB_H
#define ASTROLIB_H

#include "star.h"

double CelsiusToKelvin(double celsiusTemperature);
double KelvinToCelsius(double kelvinTemperature);

double Illumination(double lightFlow, double illuminatedSurfaceArea);

#endif // ASTROLIB_H
