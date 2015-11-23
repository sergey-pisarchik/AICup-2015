
#include "UsefullFunctions.h"

double Deg(double const rad)
{
    return rad / PI * 180;
}

double Rad(double const deg)
{
    return deg / 180. * PI;
}
double FDeg(double const rad)
{
    return fabs(rad / PI * 180);
}

double Speed(Unit const & unit)
{
    return hypot(unit.getSpeedX(), unit.getSpeedY());
}

int GetXSign(Cell const & from, Cell const & to)
{
    if (from.m_x == to.m_x)
        return 0;
    if (from.m_x < to.m_x)
        return 1;
    return -1;
}
int GetYSign(Cell const & from, Cell const & to)
{
    if (from.m_y == to.m_y)
        return 0;
    if (from.m_y < to.m_y)
        return 1;
    return -1;
}