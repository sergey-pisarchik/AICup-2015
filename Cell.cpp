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
        case LEFT  : return {m_x - 1, m_y};
        case RIGHT  : return {m_x + 1, m_y};
        case UP   :return {m_x, m_y - 1};
        case DOWN  : return {m_x, m_y + 1};
    }
    return {7,7};
}

Cell GetCell(double const dX, double const dY, Game const & game)
{
    return Cell(dX/game.getTrackTileSize(), dY/game.getTrackTileSize());
}

Cell GetCell(Unit const & unit, Game const & game)
{
    return GetCell(unit.getX(), unit.getY(), game);
}
