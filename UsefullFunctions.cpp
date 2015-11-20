
#include "UsefullFunctions.h"

double Deg(double const rad)
{
    return rad / PI * 180;
}
double FDeg(double const rad)
{
    return fabs(rad / PI * 180);
}

double Speed(Unit const & unit)
{
    return hypot(unit.getSpeedX(), unit.getSpeedY());
}