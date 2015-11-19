
#include "PathUtils.h"

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

bool CanPass(TMap const & map, Cell const & start, Direction const dir)
{
    Cell finish = start.GetNeibor(dir);
    if (!IsValidCell(map, finish))
        return false;
    if (IsDirectionOpen(GetCellType(map, start), dir) && IsDirectionOpen(GetCellType(map, finish), GetOppositeDirection(dir)))
        return true;
    return false;
}

//void DSF(TMap const & maze, Cell const & cur, Cell const & prev, Cell const & target, std::map<Cell, pair<int, Cell>> & data)
//{
//    if (cur == target)
//    {
//        if (data.count(target) ==1)
//        {
//            if (data[target].first + 1 > data[prev].first + 1 )
//                data[target] = {data[prev].first + 1, prev};
//        }
//        else
//        {
//            data[target] = {data[prev].first + 1, prev};
//        }
//        return;
//    }
//    bool bImprooved = false;
//    if (data.count(cur) == 0)
//    {
//        data[cur] = {data[prev].first + 1, prev};
//        bImprooved = true;
//    }
//    else
//    {
//        if (data[cur].first + 1 > data[prev].first + 1)
//        {
//            data[cur] = {data[prev].first + 1, prev};
//            bImprooved = true;
//        }
//    }
//    if (bImprooved)
//        for (auto dir: AllDirections())
//        {
//            if (CanPass(maze, cur, cur.GetNeibor(dir)))
//                DSF(maze, cur.GetNeibor(dir), cur, target, data);
//        }

//}

//vector<Cell> GetClosestPath(const model::World& world, Cell start, Cell finish)
//{
//    std::map<Cell, pair<int, Cell>> data;
//    data[start] = {0, start};
//    for (auto dir: AllDirections())
//    {
//        if (CanPass(world.getTilesXY(), start, start.GetNeibor(dir)))
//            DSF(world.getTilesXY(), start.GetNeibor(dir), start, finish, data);
//    }
//    vector<Cell> res(1, finish);
//    Cell cur = finish;
//    while (cur != start)
//    {
//        cur = data[cur].second;
//        res.push_back(cur);
//    }
//    reverse(res.begin(), res.end());
//    return res;
//}

void DSF(TMap const & maze,
           Cell const & cur, Cell const & prev, Cell const & target,
           std::map<Cell, pair<int, Cell>> & data)
{
    bool need_update = data.count(cur) == 0;
    need_update |= data[cur].first > data[prev].first + 1;
    if (need_update)
    {
        int prev_dist = data.count(prev) == 0 ? 0 : data[prev].first;
        data[cur] = {prev_dist + 1, prev};
    }
    if (cur == target)
        return;
    if (need_update)
        for (auto const & dir: AllDirections())
            if (CanPass(maze, cur, dir))
                DSF(maze, cur.GetNeibor(dir), cur, target, data);
}

vector<Cell> GetClosestPath(const model::World& world,
                              Cell const & start, Cell const & finish)
{
    std::map<Cell, pair<int, Cell>> data;
    DSF(world.getTilesXY(), start, start, finish, data);

    vector<Cell> res;
    if (data.count(finish) == 0)
        return res;
    Cell cur = finish;

    while (cur != start)
    {
        res.push_back(cur);
        cur = data[cur].second;
    }
    res.push_back(start);
    reverse(res.begin(), res.end());
    return res;
}










