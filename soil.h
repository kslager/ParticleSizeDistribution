#ifndef SOIL_H
#define SOIL_H

#include <boost/units/io.hpp>
#include <boost/units/systems/si/length.hpp>
//#include <boost/units/systems/si/mass_density.hpp>

using namespace boost::units;
using namespace boost::units::si;

class Soil
{
public:
    Soil( std::string name = "some soil" ) { _name = name; };

    std::string name() { return _name; };

    bool visible() { return _visible; };
    void setVisible(bool v) { _visible = v; };
//    virtual quantity<length> getDmF()=0;
//    virtual quantity<length> getD50()=0;

private:
    double d50 = 0.1;
    bool _visible = true;
    std::string _name = "some soil";

};

#endif // SOIL_H
