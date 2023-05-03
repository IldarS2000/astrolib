#ifndef ASTROLIB_STAR_H
#define ASTROLIB_STAR_H

#include <string>

class Star
{
private:
    /**
     * mass of star
     */
    double _mass{};
    /**
     * radius of star
     */
    double _radius{};
    /**
     * photosphere temperature of star
     */
    double _photosphereTemperature{};
    /**
     * heliocentric parallax in arcseconds (i.e. reciprocal of distance in parsecs), zero if unknown
     */
    double _parallax{};
    /**
     * radial velocity as fraction of light speed (i.e. light years per year), infinite if unknown
     */
    double _radvel{};
    /**
     * visual magnitude at J2000
     */
    double _Vmagnitude{};
    /**
     * blue magnitude at J2000
     */
    double _Bmagnitude{};
    /**
     * spectral type string
     */
    std::string _spectrum{};

public:
    /**
     * default constructor
     */
    Star();
    /**
     * default destructor
     */
    virtual ~Star();

    /**
     * @param mass in kg
     */
    void SetMass(double mass);
    /**
     * @param radius in km
     */
    void SetRadius(double radius);
    /**
     * @param photosphereTemperature in kelvin
     */
    void SetPhotosphereTemperature(double photosphereTemperature);

    [[nodiscard]] double GetMass() const;
    [[nodiscard]] double GetRadius() const;
    [[nodiscard]] double GetPhotosphereTemperature() const;

    /**
     * Measure of the total amount of energy radiated by a star or other celestial object per second
     */
    [[nodiscard]] double Luminosity() const;

    /**
     * Converts B-V color index (bv) to RGB color
     * @param bmv B-V color index
     * @param r red
     * @param g green
     * @param b blue
     */
    static void bmv2rgb(double bmv, double& r, double& g, double& b);
    /**
     * Converts B-V color index (bv) to temperature in Kelvin
     * @param bmv B-V color index
     * @return temperature in Kelvin
     */
    static double bmv2temp(double bmv);
    /**
     * Returns a star's absolute magnitude, given its apparent magnitude and distance in parsecs
     * @param appMag apparent magnitude
     * @param distPC distance in parsecs
     * @return absolute magnitude
     */
    static double absoluteMagnitude(double appMag, double distPC);
    /**
     * Returns a star's apparent magnitude, given its absolute magnitude and distance in parsecs
     * @param absMag absolute magnitude
     * @param distPC distance in parsecs
     * @return apparent magnitude
     */
    static double apparentMagnitude(double absMag, double distPC);
    /**
     * Returns a star's distance in parsecs from the difference between its apparent and absolute magnitudes
     * @param appMag apparent magnitude
     * @param absMag absolute magnitude
     * @return distance in parsecs
     */
    static double distanceFromMagnitude(double appMag, double absMag);
    /**
     * Returns the brightness ratio that corresponds to the magnitude difference between two stars
     * @param magDiff magnitude difference
     * @return brightness ratio
     */
    static double brightnessRatio(double magDiff);
    /**
     * Given the brightness ratio between two objects, returns their difference in magnitudes
     * @param ratio brightness ratio
     * @return difference in magnitudes
     */
    static double magnitudeDifference(double ratio);
    /**
     * Returns the combined magnitude of two stars with individual magnitudes
     */
    static double magnitudeSum(double mag1, double mag2);

    /**
     * A Moffat function describes a stellar image profile on a CCD image
     */
    static double moffatFunction(double max, double r2, double beta);
    /**
     * Computes radius in pixels from center of Moffat-function star image profile where intensity equals a given value (z)
     */
    static double moffatRadius(double z, double max, double beta);

    /**
     * spectral types
     */
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

    /**
     * luminosity classes
     */
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

    /**
     * Given a stellar spectral class string, returns integer code for spectral type
     */
    static int spectralType(const std::string& spectrum);
    /**
     * Given a stellar spectral class string, returns integer code for luminosity class
     */
    static int luminosityClass(const std::string& spectrum);
    /**
     * Given a stellar spectral class string, parses integer code for spectral type and luminosity class
     */
    static bool parseSpectrum(const std::string& spectrum, int& spectype, int& lumclass);
    /**
     * Given an integer spectral type and luminosity class code, formats and returns equivalent spectral class string
     */
    static std::string formatSpectrum(int spectype, int lumclass);
    /**
     * Converts stellar effective surface temperature in Kelvins to bolometric correction in magnitudes.
     */
    static double bolometricCorrection(double temp);
    /**
     * sConverts B-V index to stellar surface effective temperature in Kelvins
     */
    static double colorTemperature(double bmv, int lumClass);
    /**
     * Returns star's total luminosity from absolute visual magnitude (mv) and bolometric correction (bc); assumes Sun's absolute bolometric magnitude is 4.72
     * @param mv visual magnitude
     * @param bc bolometric correction
     * @return total luminosity
     */
    static double luminosity(double mv, double bc);
    /**
     * Returns star's radius in solar radii from its total bolometric luminosity (lum) and effective surface temperature in Kelvins (temp)
     */
    static double radius(double lum, double temp);
};

#endif // ASTROLIB_STAR_H
