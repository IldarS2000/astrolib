#ifndef ASTROLIB_STAR_H
#define ASTROLIB_STAR_H

namespace astrolib {

    class Star
    {
    private:
        double mass{};
        double radius{};
        double photosphereTemperature{};

    public:
        Star();
        virtual ~Star();

        void SetMass(double mass);
        void SetRadius(double radius);
        void SetPhotosphereTemperature(double photosphereTemperature);

        double GetMass() const;
        double GetRadius() const;
        double GetPhotosphereTemperature() const;

        double Luminosity() const;
    };

} // namespace astrolib

#endif // ASTROLIB_STAR_H
