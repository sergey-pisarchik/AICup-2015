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

#endif // CELL_H
