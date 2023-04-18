#include "gtest/gtest.h"
#include "astrolib.h"
#include "star.h"

TEST(Temperature, CelsiusToKelvin)
{
    ASSERT_DOUBLE_EQ(CelsiusToKelvin(-10), 263.15);
    ASSERT_DOUBLE_EQ(CelsiusToKelvin(0), 273.15);
    ASSERT_DOUBLE_EQ(CelsiusToKelvin(10), 283.15);
}

TEST(Temperature, KelvinToCelsius)
{
    ASSERT_DOUBLE_EQ(KelvinToCelsius(-10), -283.15);
    ASSERT_DOUBLE_EQ(KelvinToCelsius(0), -273.15);
    ASSERT_DOUBLE_EQ(KelvinToCelsius(10), -263.15);
}

TEST(Temperature, Illumination)
{
    ASSERT_DOUBLE_EQ(Illumination(10000, 100), 100);
    ASSERT_DOUBLE_EQ(Illumination(5000, 10), 500);
    ASSERT_DOUBLE_EQ(Illumination(5000, 50), 100);
}

TEST(Temperature, Luminosity)
{
    Star star;
    star.SetRadius(1000000000);
    star.SetPhotosphereTemperature(1000000);

    ASSERT_DOUBLE_EQ(star.Luminosity(), 7.1256287744e+35);
}