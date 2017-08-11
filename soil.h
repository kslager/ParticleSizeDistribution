#ifndef SOIL_H
#define SOIL_H

//#include <boost/units/io.hpp>
//#include <boost/units/systems/si/length.hpp>
//#include <boost/units/systems/si/mass_density.hpp>

using namespace boost::units;
using namespace boost::units::si;

class Soil
{
public:
    Soil() {};

    virtual quantity<length> getDmF()=0;
    virtual quantity<length> getD50()=0;

private:

};

#endif // SOIL_H
