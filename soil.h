#ifndef SOIL_H
#define SOIL_H

#include <boost/units/io.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/mass_density.hpp>

using namespace boost::units;
using namespace boost::units::si;

class Soil
{
public:
    Soil();
    ~Soil();

    void setName(std::string name);
    std::string getName();

    void setDescription(std::string description);
    std::string getDescription();

    // set the particle fraction by percentage, e.g. d50 is set by
    // setDiameter(50, d)
    void setDiameter(int n, quantity<length> d);

    // set the particle fraction by the index in the particle vector, e.g. d50
    // is set by setDiameterIndex(5, d)
    void setDiameterIndex(int n, quantity<length> d);

    quantity<length> getDmf();

private:
    // A descriptive name for the soil type, e.g. "Fine sand"
    std::string _name;

    // A description for the soil, e.g. "1900 kg/m3, 0.016 - 0.2 mm"
    std::string _description;

    // The particle sizes d0, d10, ..., d90, d100.
    quantity<length> _d[11];

    // The minimum and maximum particle sizes which are applicable for this soil
    quantity<length> _dmin;
    quantity<length> _dmax;

    // Grain density
    quantity<mass_density> _rho_s = 2650 * kilogram_per_cubic_meter;

    // In situ density
    quantity<mass_density> _rho_sit;
};

#endif // SOIL_H


/*
sand(1).d = [
    0.0336309228718879
    0.0595849288565138
    0.0784757163748353
    0.0900605761092338
    0.096991665042042
    0.103355633357786
    0.108976770650809
    0.114903621173393
    0.122442856675688
    0.137572925508522
    0.195133363519118 ];
sand(1).dmin = 0.016;
sand(1).dmax = 0.2;
sand(1).name = 'Fine sand';
sand(1).desc = '1900 kg/m³, 0.016 - 0.2 mm';
*/
