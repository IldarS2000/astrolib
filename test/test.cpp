#include "gtest/gtest.h"
#include "astrolib.h"
#include "star.h"

TEST(Temperature, CelsiusToKelvin)
{
    ASSERT_DOUBLE_EQ(CelsiusToKelvin(-10), 263.15);
    ASSERT_DOUBLE_EQ(CelsiusToKelvin(0), 273.15);
    ASSERT_DOUBLE_EQ(CelsiusToKelvin(10), 283.15);
    ASSERT_DOUBLE_EQ(CelsiusToKelvin(102), 375.15);
    ASSERT_DOUBLE_EQ(CelsiusToKelvin(200), 473.15);
    ASSERT_DOUBLE_EQ(CelsiusToKelvin(-11), 262.15);
    ASSERT_DOUBLE_EQ(CelsiusToKelvin(-126.928), 146.222);
    ASSERT_DOUBLE_EQ(CelsiusToKelvin(-196.234), 76.916);
    ASSERT_DOUBLE_EQ(CelsiusToKelvin(-204.800), 68.35);
    ASSERT_DOUBLE_EQ(CelsiusToKelvin(94.872), 368.022);
}

TEST(Temperature, KelvinToCelsius)
{
    ASSERT_DOUBLE_EQ(KelvinToCelsius(-10), -283.15);
    ASSERT_DOUBLE_EQ(KelvinToCelsius(0), -273.15);
    ASSERT_DOUBLE_EQ(KelvinToCelsius(10), -263.15);
    ASSERT_DOUBLE_EQ(CelsiusToKelvin(102), 375.15);
    ASSERT_DOUBLE_EQ(CelsiusToKelvin(200), 473.15);
    ASSERT_DOUBLE_EQ(CelsiusToKelvin(-11), 262.15);
    ASSERT_DOUBLE_EQ(KelvinToCelsius(94.872), -178.278);
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