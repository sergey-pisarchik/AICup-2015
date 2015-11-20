#ifndef CELL_H
#define CELL_H

#include "CommonDefines.h"
using namespace model;

struct Cell
{
public:
    Cell() = default;
    Cell(int x, int y);
    bool operator<(Cell const & other) const;
    bool operator==(Cell const & other) const;
    bool operator!=(Cell const & other) const;
    Cell GetNeibor(Direction const dir) const;
    int m_x;
    int m_y;
};

Cell GetCell(double const dX, double const dY, Game const & game);
Cell GetCell(Unit const & unit, Game const & game);

template <class TAr>
TAr & operator<< (TAr & ar, Cell const & cell)
{
    ar << cell.m_x << " " << cell.m_y;
    return ar;
}

#endif // CELL_H
