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

TEST(bv, bmv2temp)
{
    ASSERT_DOUBLE_EQ(Star::bmv2temp(1.22), 4269.8553250501309);
    ASSERT_DOUBLE_EQ(Star::bmv2temp(5.7553), 1435.3243961273329);
    ASSERT_DOUBLE_EQ(Star::bmv2temp(0), 10125.237191650855);
    ASSERT_DOUBLE_EQ(Star::bmv2temp(-50.111), -204.7373022533063);
}

TEST(Spectrum, luminosityClass)
{
    ASSERT_EQ(Star::luminosityClass("g"), Star::LumClass::III);
    ASSERT_EQ(Star::luminosityClass("D"), Star::LumClass::VII);
    ASSERT_EQ(Star::luminosityClass("sgd"), Star::LumClass::IV);
    ASSERT_EQ(Star::luminosityClass("sdg"), Star::LumClass::VI);
    ASSERT_EQ(Star::luminosityClass("cccc"), Star::LumClass::Iab);
    ASSERT_EQ(Star::luminosityClass("dog"), Star::LumClass::V);
}

TEST(Temperature,Radius)
{
    ASSERT_DOUBLE_EQ(Star::radius(0,1), 0.0);
    ASSERT_DOUBLE_EQ(Star::radius(10,15), 467917.3062765327);
    ASSERT_DOUBLE_EQ(Star::radius(0,-2), 0.0);
    ASSERT_DOUBLE_EQ(Star::radius(100, 256), 5080.0933837890625);

}

TEST(bmv, RGB)
{
    double r,g,b;

    Star::bmv2rgb(123, r, g, b);
    ASSERT_EQ(r, 1);
    ASSERT_EQ(g, 0);
    ASSERT_EQ(b, 0);

    Star::bmv2rgb(-456,r, g, b);
    ASSERT_EQ(r, 0.61);
    ASSERT_EQ(g, 0.7);
    ASSERT_EQ(b, 1);

    Star::bmv2rgb(0,r, g, b);
    ASSERT_EQ(r ,0.83);
    ASSERT_EQ(g, 0.87);
    ASSERT_EQ(b, 1);

    Star::bmv2rgb(2.56,r, g, b);
    ASSERT_EQ(r , 1);
    ASSERT_EQ(g, 0);
    ASSERT_EQ(b, 0);
}

TEST(moffatFunction, Star)
{
    ASSERT_DOUBLE_EQ(Star::moffatFunction(1234, 54, 34), 8.2981965430403318e-57);
    ASSERT_DOUBLE_EQ(Star::moffatFunction(0, 0, 0), 0);
    ASSERT_DOUBLE_EQ(Star::moffatFunction(-3, -4, -6), -2187);
    ASSERT_DOUBLE_EQ(Star::moffatFunction(10, -6, 0), 10);
    ASSERT_DOUBLE_EQ(Star::moffatFunction(-6, 10, 0), -6);
    ASSERT_DOUBLE_EQ(Star::moffatFunction(0, -3, -50), 0);
}

TEST(moffatRadius, Star)
{
    ASSERT_DOUBLE_EQ(Star::moffatRadius(1, 2, 3), 0.50982452853395865);
    ASSERT_DOUBLE_EQ(Star::moffatFunction(7, 10, 0.5), 2.1105794120443453);
    ASSERT_DOUBLE_EQ(Star::moffatFunction(-3.6, 10, -2), -435.60000000000002);
    ASSERT_DOUBLE_EQ(Star::moffatFunction(106, 64, 0), 106);
    ASSERT_DOUBLE_EQ(Star::moffatFunction(12, -3,-3), -96);
    ASSERT_DOUBLE_EQ(Star::moffatFunction(10, 13, -50), 2.024891623976442e+58);
}

TEST(magnitudeSum, Star)
{
    ASSERT_DOUBLE_EQ(Star::magnitudeSum(1, 3), 2.8402699146415511);
    ASSERT_DOUBLE_EQ(Star::magnitudeSum(0, 2.2245), 2.0928764221021168);
    ASSERT_DOUBLE_EQ(Star::magnitudeSum(1.4534, 2.4545), 2.0909619507290649);
    ASSERT_DOUBLE_EQ(Star::magnitudeSum(-2.34, 34.456), 34.456000000000003);
    ASSERT_DOUBLE_EQ(Star::magnitudeSum(-1, -5), -9.0269355637798938);
    ASSERT_DOUBLE_EQ(Star::magnitudeSum(0, 0), -0.75257498915995302);
    ASSERT_DOUBLE_EQ(Star::magnitudeSum(-1233123, 567466), 567466);
}

TEST(magnitudeDiff, Star)
{
    ASSERT_DOUBLE_EQ(Star::magnitudeDifference(1), 0);
    ASSERT_DOUBLE_EQ(Star::magnitudeDifference(60.356), -4.4518011246653284);
    ASSERT_DOUBLE_EQ(Star::magnitudeDifference(765.43), -7.2097636995263024);
    ASSERT_DOUBLE_EQ(Star::magnitudeDifference(9835.6), -9.9820021457021966);
}

TEST(brightnessRatio, Star)
{
    ASSERT_DOUBLE_EQ(Star::brightnessRatio(123), 1.5848931924611239e+49);
    ASSERT_DOUBLE_EQ(Star::brightnessRatio(-1), 0.3981071705534972);
    ASSERT_DOUBLE_EQ(Star::brightnessRatio(0), 1);
    ASSERT_DOUBLE_EQ(Star::brightnessRatio(-34.34), 1.8365383433483437e-14);
}

TEST(colorTemperature, Star)
{
    ASSERT_DOUBLE_EQ(Star::colorTemperature(1, 2), 4973.0488259245667);
    ASSERT_DOUBLE_EQ(Star::colorTemperature(-1, 2), 196849223353.16696);
    ASSERT_DOUBLE_EQ(Star::colorTemperature(1, -2), 4973.0488259245667);
    ASSERT_DOUBLE_EQ(Star::colorTemperature(1.123124, 2.4535), 4716.3964500009688);
    ASSERT_DOUBLE_EQ(Star::colorTemperature(0, 0), 10293.42091992655);
}

TEST(bolometricCorrection, Star)
{
    ASSERT_DOUBLE_EQ(Star::bolometricCorrection(123), -1547.9847678631068);
    ASSERT_DOUBLE_EQ(Star::bolometricCorrection(1.5), -16450.311387237994);
}

TEST(distanceFromMagnitude, Star)
{
    ASSERT_DOUBLE_EQ(Star::distanceFromMagnitude(1, 2), 6.3095734448019334);
    ASSERT_DOUBLE_EQ(Star::distanceFromMagnitude(-1, -2), 15.848931924611133);
    ASSERT_DOUBLE_EQ(Star::distanceFromMagnitude(-1, 2), 2.5118864315095801);
    ASSERT_DOUBLE_EQ(Star::distanceFromMagnitude(1, -2), 39.810717055349734);
    ASSERT_DOUBLE_EQ(Star::distanceFromMagnitude(0, 0), 10);
}

TEST(apparentMagnitude, Star)
{
    ASSERT_DOUBLE_EQ(Star::apparentMagnitude(1, 2), -2.4948500216800937);
    ASSERT_DOUBLE_EQ(Star::apparentMagnitude(-1, 2), -4.4948500216800937);
}

TEST(absoluteMagnitude, Star)
{
    ASSERT_DOUBLE_EQ(Star::absoluteMagnitude(1, 2), 4.4948500216800937);
    ASSERT_DOUBLE_EQ(Star::absoluteMagnitude(-1, 2), 2.4948500216800937);
}