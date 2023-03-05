#include "gtest/gtest.h"
#include "astrolib.h"

TEST(Temperature, CelsiusToKelvin)
{
    ASSERT_DOUBLE_EQ(astrolib::CelsiusToKelvin(-10), 263.15);
    ASSERT_DOUBLE_EQ(astrolib::CelsiusToKelvin(0), 273.15);
    ASSERT_DOUBLE_EQ(astrolib::CelsiusToKelvin(10), 283.15);
}

TEST(Temperature, KelvinToCelsius)
{
    ASSERT_DOUBLE_EQ(astrolib::KelvinToCelsius(-10), -283.15);
    ASSERT_DOUBLE_EQ(astrolib::KelvinToCelsius(0), -273.15);
    ASSERT_DOUBLE_EQ(astrolib::KelvinToCelsius(10), -263.15);
}