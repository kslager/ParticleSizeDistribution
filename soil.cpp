#include "soil.h"

Soil::Soil() {
}

Soil::~Soil() {}

void Soil::setName(std::string name)
{
    _name = name;
}

std::string Soil::getName()
{
    return _name;
}

void Soil::setDescription(std::string desc)
{
    _description = desc;
}

std::string Soil::getDescription()
{
    return _description;
}

void Soil::setDiameter(int n, quantity<length> d)
{
    setDiameterIndex(n/10, d);
}

void Soil::setDiameterIndex(int n, quantity<length> d)
{
    _d[n] = d;
}

quantity<length> Soil::getDmf()
{
    quantity<length> result = 0.0 * meters;

    for( int i = 9; i--; )
        result += _d[i+1];

    return result / 9.0;
}
