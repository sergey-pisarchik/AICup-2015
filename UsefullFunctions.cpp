
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

Direction GetDirection(Unit const & unit)
{
    double DegAngle = Deg(unit.getAngle());
    if (DegAngle > -45 && DegAngle <= 45)
        return RIGHT;
    if (DegAngle > 45 && DegAngle <= 135)
        return DOWN;
    if (DegAngle > 135 || DegAngle <= -135)
        return LEFT;
    if (DegAngle > -135 && DegAngle <= -45)
        return UP;
    
    return RIGHT;
    
}

std::pair<double, double> GetCornerCoords(Cell const & cell, int corner, Game const & game)
{
    double half = 0.5 * game.getTrackTileSize();
    double centerX = (cell.m_x + 0.5) * game.getTrackTileSize();
    double centerY = (cell.m_y + 0.5) * game.getTrackTileSize();
    
    pair<double, double> res = {centerX, centerY};
    if (corner == 0)
    {
        res.first += half;
        res.second += half;
    }
    if (corner == 1)
    {
        res.first -= half;
        res.second += half;
    }
    if (corner == 2)
    {
        res.first += half;
        res.second -= half;
    }
    if (corner == 3)
    {
        res.first -= half;
        res.second -= half;
    }
    return res;
    
}