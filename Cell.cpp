#include "Cell.h"
 Cell::Cell(int x, int y)
     :m_x(x), m_y(y)
 {

 }

bool Cell::operator==(Cell const & other) const
{
    return m_x == other.m_x && m_y == other.m_y;
}
bool Cell::operator!=(Cell const & other) const
{
    return !(operator==(other));
}
bool Cell::operator<(Cell const & other) const
{
    if (m_x == other.m_x)
        return m_y < other.m_y;
    return m_x < other.m_x;
}

Cell Cell::GetNeibor(Direction const dir) const
{
    switch (dir) {
    case LEFT:

        break;
    default:
        break;
    }
}

Cell GetCell(double const dX, double const dY, Game const & game)
{
    return Cell(dX/game.getTrackTileSize(), dY/game.getTrackTileSize());
}
