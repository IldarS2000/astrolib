#include <string>
#include <cmath>
#include "star.h"
#include "constants.h"

Star::Star()  = default;
Star::~Star() = default;

void Star::SetMass(const double mass)
{
    this->_mass = mass;
}
void Star::SetRadius(const double radius)
{
    this->_radius = radius;
}
void Star::SetPhotosphereTemperature(const double photosphereTemperature)
{
    this->_photosphereTemperature = photosphereTemperature;
}

double Star::GetMass() const
{
    return this->_mass;
}
double Star::GetRadius() const
{
    return this->_radius;
}
double Star::GetPhotosphereTemperature() const
{
    return this->_photosphereTemperature;
}

double Star::Luminosity() const
{
    return 4 * PI_NUMBER * std::pow(this->_radius, 2) * STEFAN_BOLTZMANN_CONSTANT *
           std::pow(this->_photosphereTemperature, 4);
}

// Converts B-V color index (bv) to RGB color
void Star::bmv2rgb(double bv, double& r, double& g, double& b)
{
    double t = r = g = b = 0.0;

    if (bv < -0.4) {
        bv = -0.4;
    }

    if (bv > 2.0) {
        bv = 2.0;
    }

    // red
    if (bv >= -0.40 && bv < 0.00) {
        t = (bv + 0.40) / (0.00 + 0.40);
        r = 0.61 + (0.11 * t) + (0.1 * t * t);
    } else if (bv >= 0.00 && bv < 0.40) {
        t = (bv - 0.00) / (0.40 - 0.00);
        r = 0.83 + (0.17 * t);
    } else if (bv >= 0.40 && bv < 2.10) {
        t = (bv - 0.40) / (2.10 - 0.40);
        r = 1.00;
    }

    // green
    if (bv >= -0.40 && bv < 0.00) {
        t = (bv + 0.40) / (0.00 + 0.40);
        g = 0.70 + (0.07 * t) + (0.1 * t * t);
    } else if (bv >= 0.00 && bv < 0.40) {
        t = (bv - 0.00) / (0.40 - 0.00);
        g = 0.87 + (0.11 * t);
    } else if (bv >= 0.40 && bv < 1.60) {
        t = (bv - 0.40) / (1.60 - 0.40);
        g = 0.98 - (0.16 * t);
    } else if (bv >= 1.60 && bv < 2.00) {
        t = (bv - 1.60) / (2.00 - 1.60);
        g = 0.82 - (0.5 * t * t);
    }

    // blue
    if (bv >= -0.40 && bv < 0.40) {
        t = (bv + 0.40) / (0.40 + 0.40);
        b = 1.00;
    } else if (bv >= 0.40 && bv < 1.50) {
        t = (bv - 0.40) / (1.50 - 0.40);
        b = 1.00 - (0.47 * t) + (0.1 * t * t);
    } else if (bv >= 1.50 && bv < 1.94) {
        t = (bv - 1.50) / (1.94 - 1.50);
        b = 0.63 - (0.6 * t * t);
    }
}

// Converts B-V color index (bv) to temperature in Kelvin
double Star::bmv2temp(double bv)
{
    return 4600.0 * ((1.0 / ((0.92 * bv) + 1.7)) + (1.0 / ((0.92 * bv) + 0.62)));
}

// Converts B-V index to stellar surface effective temperature in Kelvins
double Star::colorTemperature(double bv, int lumClass)
{
    double t = 0.0;

    if (lumClass <= LumClass::Ib) {
        t = 4.012559732366214 - 1.055043117465989 * bv + 2.133394538571825 * bv * bv -
            2.459769794654992 * bv * bv * bv + 1.349423943497744 * bv * bv * bv * bv -
            0.283942579112032 * bv * bv * bv * bv * bv;
    } else {
        t = 3.979145106714099 - 0.654992268598245 * bv + 1.740690042385095 * bv * bv -
            4.608815154057166 * bv * bv * bv + 6.792599779944473 * bv * bv * bv * bv -
            5.396909891322525 * bv * bv * bv * bv * bv + 2.192970376522490 * bv * bv * bv * bv * bv * bv -
            0.359495739295671 * bv * bv * bv * bv * bv * bv * bv;
    }

    return pow(10.0, t);
}

// Converts stellar effective surface temperature in Kelvins to bolometric correction in magnitudes.
double Star::bolometricCorrection(double t)
{
    double bc = INFINITY;

    t = log10(t);
    if (t > 3.9) {
        bc = -0.118115450538963E+06 + 0.137145973583929E+06 * t - 0.636233812100225E+05 * t * t +
             0.147412923562646E+05 * t * t * t - 0.170587278406872E+04 * t * t * t * t +
             0.788731721804990E+02 * t * t * t * t * t;
    } else if (t > 3.7) {
        bc = -0.370510203809015E+05 + 0.385672629965804E+05 * t - 0.150651486316025E+05 * t * t +
             0.261724637119416E+04 * t * t * t - 0.170623810323864E+03 * t * t * t * t;
    } else {
        bc = -0.190537291496456E+05 + 0.155144866764412E+05 * t - 0.421278819301717E+04 * t * t +
             0.381476328422343E+03 * t * t * t;
    }

    return bc;
}

// Returns a star's absolute magnitude, given its apparent magnitude and distance in parsecs
double Star::absoluteMagnitude(double appMag, double dist)
{
    if (dist > 0.0 && dist < INFINITY) {
        return appMag - 5.0 * (log10(dist) - 1.0);
    } else {
        return -INFINITY;
    }
}

// Returns a star's apparent magnitude, given its absolute magnitude and distance in parsecs
double Star::apparentMagnitude(double absMag, double dist)
{
    if (dist > 0.0 && dist < INFINITY) {
        return absMag + 5.0 * (log10(dist) - 1.0);
    } else {
        return dist <= 0.0 ? -INFINITY : INFINITY;
    }
}

// Returns a star's distance in parsecs from the difference between its apparent and absolute magnitudes
double Star::distanceFromMagnitude(double appMag, double absMag)
{
    return pow(10.0, (appMag - absMag) / 5.0 + 1.0);
}

// Returns the brightness ratio that corresponds to the magnitude difference between two stars
double Star::brightnessRatio(double magDiff)
{
    if (std::isinf(magDiff)) {
        return magDiff > 0.0 ? INFINITY : 0.0;
    } else {
        return pow(10.0, magDiff / 2.5);
    }
}

// Given the brightness ratio between two objects, returns their difference in magnitudes
double Star::magnitudeDifference(double ratio)
{
    return -2.5 * log10(ratio);
}

// Returns the combined magnitude of two stars with individual magnitudes
double Star::magnitudeSum(double mag1, double mag2)
{
    if (std::isinf(mag2)) {
        return mag1;
    } else if (std::isinf(mag1)) {
        return mag2;
    } else {
        return mag2 + magnitudeDifference(1.0 + brightnessRatio(mag1 - mag2));
    }
}

// A Moffat function describes a stellar image profile on a CCD image
double Star::moffatFunction(double max, double r2, double beta)
{
    return max / pow(1.0 + r2, beta);
}

// Computes radius in pixels from center of Moffat-function star image profile where intensity equals a given value (z)
double Star::moffatRadius(double z, double max, double beta)
{
    return sqrt(pow(max / z, 1.0 / beta) - 1.0);
}

// Given a stellar spectral class string, returns integer code for spectral type
int Star::spectralType(const std::string& spectrum)
{
    int spectype          = 0;
    static char types[14] = {'W', 'O', 'B', 'A', 'F', 'G', 'K', 'M', 'L', 'T', 'C', 'R', 'N', 'S'};

    for (int i = 0; i < spectrum.length(); i++) {
        for (int k = 0; k < 14; k++) {
            if (spectrum[i] == types[k]) {
                spectype = k * 10;
                i++;
                if (spectrum[i] >= '0' && spectrum[i] <= '9') {
                    spectype += spectrum[i] - '0';
                }

                return spectype;
            }
        }
    }

    return 0;
}

// Given a stellar spectral class string, returns integer code for luminosity class
int Star::luminosityClass(const std::string& spectrum)
{
    int i        = 0;
    int lumclass = 0;

    if (spectrum[0] == 'c') {
        lumclass = LumClass::Iab;
    }

    if (spectrum[0] == 'g') {
        lumclass = LumClass::III;
    }

    if (spectrum[0] == 's' && spectrum.size() >= 2) {
        if (spectrum[1] == 'g') {
            lumclass = LumClass::IV;
        } else if (spectrum[1] == 'd') {
            lumclass = LumClass::VI;
        }
    }

    if (spectrum[0] == 'd') {
        lumclass = LumClass::V;
    }

    if (spectrum[0] == 'D') {
        lumclass = LumClass::VII;
    }

    if (lumclass > 0)
        return lumclass;

    i = (int)spectrum.find_first_of("IV");
    if (i == std::string::npos) {
        return 0;
    }

    if (spectrum.compare(i, 3, "VII", 3) == 0) {
        lumclass = LumClass::VII;
    }
    else if (spectrum.compare(i, 2, "VI", 2) == 0) {
        lumclass = LumClass::VI;
    }
    else if (spectrum.compare(i, 1, "V", 1) == 0) {
        lumclass = LumClass::V;
    }

    else if (spectrum.compare(i, 3, "Iab", 3) == 0)
        lumclass = LumClass::Iab;
    else if (spectrum.compare(i, 3, "IAB", 3) == 0)
        lumclass = LumClass::Iab;
    else if (spectrum.compare(i, 3, "Ia0", 3) == 0)
        lumclass = LumClass::Ia0;
    else if (spectrum.compare(i, 3, "IA0", 3) == 0)
        lumclass = LumClass::Ia0;
    else if (spectrum.compare(i, 3, "IA+", 3) == 0)
        lumclass = LumClass::Ia0;
    else if (spectrum.compare(i, 2, "Ia", 2) == 0)
        lumclass = LumClass::Ia;
    else if (spectrum.compare(i, 2, "IA", 2) == 0)
        lumclass = LumClass::Ia;
    else if (spectrum.compare(i, 2, "Ib", 2) == 0)
        lumclass = LumClass::Ib;
    else if (spectrum.compare(i, 2, "IB", 2) == 0)
        lumclass = LumClass::Ib;

    else if (spectrum.compare(i, 3, "III", 3) == 0)
        lumclass = LumClass::III;
    else if (spectrum.compare(i, 2, "II", 2) == 0)
        lumclass = LumClass::II;
    else if (spectrum.compare(i, 2, "IV", 2) == 0)
        lumclass = LumClass::IV;

    return lumclass;
}

// Given a stellar spectral class string, parses integer code for spectral type and luminosity class
bool Star::parseSpectrum(const std::string& spectrum, int& spectype, int& lumclass)
{
    spectype = spectralType(spectrum);
    lumclass = luminosityClass(spectrum);
    return spectype || lumclass;
}

// Given an integer spectral type and luminosity class code,
// formats and returns equivalent spectral class string
std::string Star::formatSpectrum(int spectype, int lumclass)
{
    std::string spectrum;
    static char types[14] = {'W', 'O', 'B', 'A', 'F', 'G', 'K', 'M', 'L', 'T', 'C', 'R', 'N', 'S'};

    if (lumclass == LumClass::VII)
        spectrum.append(1, 'D');

    if (spectype > SpecType::W0 && spectype < SpecType::T0 + 9) {
        spectrum.append(1, types[spectype / 10]);
        spectrum.append(1, '0' + spectype % 10);
    }

    if (lumclass == LumClass::Ia0)
        spectrum.append("Ia0");
    else if (lumclass == LumClass::Ia)
        spectrum.append("Ia");
    else if (lumclass == LumClass::Iab)
        spectrum.append("Iab");
    else if (lumclass == LumClass::Ib)
        spectrum.append("Ib");
    else if (lumclass == LumClass::II)
        spectrum.append("II");
    else if (lumclass == LumClass::III)
        spectrum.append("III");
    else if (lumclass == LumClass::IV)
        spectrum.append("IV");
    else if (lumclass == LumClass::V)
        spectrum.append("V");
    else if (lumclass == LumClass::VI)
        spectrum.append("VI");

    return spectrum;
}

// Returns estimate of star distance based on absolute magnitude derived from spectral class,
// and star's apparent visual and blue magnitudes. Distance estimate is returned in parsecs
// and will be INFINITY if not determined.
double Star::spectralDistance(const std::string& spectrum, double vmag, double bmag)
{
    if (std::isinf(vmag) && std::isinf(bmag))
        return INFINITY;

    int spectype = 0, lumclass = 0;
    parseSpectrum(spectrum, spectype, lumclass);
    if (spectype == 0)
        return INFINITY;

    // If luminosity class is not present, we'll guess that "early" spectral types are main-sequence,
    // and "late" types are giants. Late main-sequence stars are intrinsically faint, and (probably)
    // nearby enough to have their distances already known from trigonometric parallax.

    if (lumclass == 0)
        lumclass = spectype < SpecType::A0 ? LumClass::V : LumClass::III;

    // Get spectral class info. If visual magnitude is not available,
    // compute it from blue magnitude and expected color index.

    SpecInfo info = spectralClassInfo(spectype, lumclass);
    if (info.Mv < INFINITY) {
        if (std::isinf(vmag))
            vmag = bmag - info.BV;

        // Compute distance from difference between apparent and absolute visual magnitude.
        // If farther than 100 parsecs, estimate insterstellar dust absorption and recompute.

        double d = distanceFromMagnitude(vmag, info.Mv);
        if (d > 100.0) {
            // If both visual and blue magnitudes are available, compute B-V color
            // excess and estimate absoption as 3 x excess. This can never be negative!
            // Then recompute distance in parsecs, including absorption.

            double a = bmag < INFINITY ? (bmag - vmag) - info.BV : 0.0;
            a        = a < 0.0 ? 0.0 : 3.0 * a;
            d        = distanceFromMagnitude(vmag - a, info.Mv);
        }

        return d;
    }

    return INFINITY;
}

// Returns star's total luminosity from absolute visual magnitude (mv)
// and bolometric correction (bc); assumes Sun's absolute bolometric magnitude is 4.72.
double Star::luminosity(double mv, double bc)
{
    return brightnessRatio(4.725 - mv - bc);
}

// Returns star's radius in solar radii from its total bolometric luminosity (lum)
// and effective surface temperature in Kelvins (temp).
double Star::radius(double lum, double temp)
{
    temp = 5770.0 / temp;
    return temp * temp * sqrt(lum);
}