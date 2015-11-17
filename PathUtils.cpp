
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

bool CanPass(TMap const & map, Cell const & start, Cell const & finish)
{
    for (auto dir: AllDirections())
        if (IsDirectionOpen(GetCellType(map, start), dir) && IsDirectionOpen(GetCellType(map, finish), GetOppositeDirection(dir)))
            return true;
    return false;
}

bool IsValidCell(TMap const & map, Cell const & cell)
{
    if (cell.m_x < 0)
        return false;
    if (cell.m_y < 0)
        return false;
    if (cell.m_x >= map.size())
        return false;
    if (cell.m_y >= map.size())
        return false;
    return true;
}

void WSF(TMap const & maze, Cell const & cur, Cell const & prev, Cell const & target, std::map<Cell, pair<int, Cell>> & data)
{
    if (cur == target)
    {
        data[target] = {data[prev].first + 1, prev};
        return;
    }
    if (data.count(cur) == 0)
        data[cur] = {data[prev].first + 1, prev};
    else
    {
        if (data[cur].first + 1 > data[prev].first + 1)
            data[cur] = {data[prev].first + 1, prev};
    }
    for (auto dir: AllDirections())
    {
        if (CanPass(maze, cur, cur.GetNeibor(dir)))
            WSF(maze, cur.GetNeibor(dir), cur, target, data);
    }

}

vector<Cell> GetClosestPath(const model::World& world, Cell start, Cell finish)
{
    std::map<Cell, pair<int, Cell>> data;
    data[start] = {0, start};
    for (auto dir: AllDirections())
    {
        if (CanPass(world.getTilesXY(), start, start.GetNeibor(dir)))
            WSF(world.getTilesXY(), start, start.GetNeibor(dir), finish, data);
    }
    vector<Cell> res(1, finish);
    Cell cur = finish;
    while (cur != start)
    {
        cur = data[cur].second;
        res.push_back(cur);
    }
    reverse(res.begin(), res.end());
    return res;
}


