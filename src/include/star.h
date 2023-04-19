#ifndef ASTROLIB_STAR_H
#define ASTROLIB_STAR_H

#include <string>

class Star
{
private:
    double _mass{};
    double _radius{};
    double _photosphereTemperature{};

    double _parallax{}; // heliocentric parallax in arcseconds (i.e. reciprocal of distance in parsecs), zero if unknown
    double _radvel{};   // radial velocity as fraction of light speed (i.e. light years per year), infinite if unknown
    double _Vmagnitude{};    // visual magnitude at J2000
    double _Bmagnitude{};    // blue magnitude at J2000
    std::string _spectrum{}; // Spectral type string

public:
    Star();
    virtual ~Star();

    void SetMass(double mass);
    void SetRadius(double radius);
    void SetPhotosphereTemperature(double photosphereTemperature);

    [[nodiscard]] double GetMass() const;
    [[nodiscard]] double GetRadius() const;
    [[nodiscard]] double GetPhotosphereTemperature() const;

    [[nodiscard]] double Luminosity() const;

    static void bmv2rgb(double bmv, double& r, double& g, double& b);
    static double bmv2temp(double bmv);
    static double absoluteMagnitude(double appMag, double distPC);
    static double apparentMagnitude(double absMag, double distPC);
    static double distanceFromMagnitude(double appMag, double absMag);
    static double brightnessRatio(double magDiff);
    static double magnitudeDifference(double ratio);
    static double magnitudeSum(double mag1, double mag2);

    static double moffatFunction(double max, double r2, double beta);
    static double moffatRadius(double z, double max, double beta);

    // Spectral types and luminosity classes
    enum SpecType
    {
        W0 = 0, // Wolf-Rayet stars
        O0 = 10,
        B0 = 20,
        A0 = 30,
        F0 = 40,
        G0 = 50,
        K0 = 60,
        M0 = 70,
        L0 = 80,  // Brown dwarfs
        T0 = 90,  // Brown dwarfs
        C0 = 100, // Carbon stars
        R0 = 110, // Carbon stars (obsolete)
        N0 = 120, // Carbon stars (obsolete)
        S0 = 130, // Carbon stars (obsolete)
    };

    enum LumClass
    {
        Ia0 = 1, // hypergiants
        Ia  = 2, // luminous supergiants
        Iab = 3, // intermediate supergiants, c
        Ib  = 4, // less luminous supergiants
        II  = 5, // bright giants
        III = 6, // giants, g
        IV  = 7, // subgiants, sg
        V   = 8, // main-sequence, d
        VI  = 9, // subdwarfs, sd
        VII = 10 // white dwarfs, D
    };

    static int spectralType(const std::string& spectrum);
    static int luminosityClass(const std::string& spectrum);
    static bool parseSpectrum(const std::string& spectrum, int& spectype, int& lumclass);
    static std::string formatSpectrum(int spectype, int lumclass);
    static double bolometricCorrection(double temp);
    static double colorTemperature(double bmv, int lumClass);
    static double luminosity(double mv, double bc);
    static double radius(double lum, double temp);
};

#endif // ASTROLIB_STAR_H
