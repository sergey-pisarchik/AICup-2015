
#include <PathUtils.h>

Direction GetOppositeDirection(Direction dir)
{
    switch (dir) {
    case LEFT:
        return RIGHT;
    case RIGHT:
        return LEFT;
    case UP:
        return DOWN;
    case DOWN:
        return UP;
    }
    return UP;
}

bool IsDirectionOpen(TileType const ttype, Direction dir)
{
    if (ttype == CROSSROADS)
        return true;
    switch (dir) {
    case LEFT:
        return (ttype == HORIZONTAL || ttype == RIGHT_TOP_CORNER || ttype == RIGHT_BOTTOM_CORNER
                || ttype == LEFT_HEADED_T || ttype == BOTTOM_HEADED_T || ttype == TOP_HEADED_T);
    case RIGHT:
        return (ttype == HORIZONTAL || ttype == LEFT_TOP_CORNER || ttype == LEFT_BOTTOM_CORNER
                || ttype == RIGHT_HEADED_T || ttype == BOTTOM_HEADED_T || ttype == TOP_HEADED_T);
    case UP:
        return (ttype == VERTICAL || ttype == LEFT_BOTTOM_CORNER || ttype == RIGHT_BOTTOM_CORNER
                || ttype == LEFT_HEADED_T || ttype == BOTTOM_HEADED_T || ttype == RIGHT_HEADED_T);
    case DOWN:
        return (ttype == VERTICAL || ttype == RIGHT_TOP_CORNER || ttype == LEFT_TOP_CORNER
                || ttype == LEFT_HEADED_T || ttype == RIGHT_HEADED_T || ttype == TOP_HEADED_T);
    }
    return false;
}

TileType GetCellType(TMap const & map, Cell const & cell)
{
    return map[cell.m_x][cell.m_y];
}

bool CanPath(TMap const & map, Cell const & start, Cell const & finish)
{
    for (auto dir: AllDirections())
        if (IsDirectionOpen(GetCellType(map, start), dir) && IsDirectionOpen(GetCellType(map, finish), GetOppositeDirection(dir)))
            return true;
    return false;
}

vector<Cell> GetClosestPath(const model::World& world, Cell start, Cell finish)
{
    return vector<Cell>();
}


