
#include "PathUtils.h"
#include "Cell.h"

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
                    || ttype == LEFT_HEADED_T || ttype == TOP_HEADED_T || ttype == RIGHT_HEADED_T);
        case DOWN:
            return (ttype == VERTICAL || ttype == RIGHT_TOP_CORNER || ttype == LEFT_TOP_CORNER
                    || ttype == LEFT_HEADED_T || ttype == RIGHT_HEADED_T || ttype == BOTTOM_HEADED_T);
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
    if (cell.m_y >= map[0].size())
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

typedef pair<Cell, Direction> MapKeyT;
typedef std::map<MapKeyT, pair<int, MapKeyT>> MapT;

void DSF(TMap const & maze,
         MapKeyT const & cur, MapKeyT const & prev, Cell const & target,
         MapT & data)
{
    bool IsOpposite = GetOppositeDirection(prev.second) == cur.second;
    bool need_update = data.count(cur) == 0;
    need_update |= data[cur].first > data[prev].first + (IsOpposite ? 3 : 1);
    if (need_update)
    {
        int prev_dist = data.count(prev) == 0 ? 0 : data[prev].first;
        data[cur] = {prev_dist + (IsOpposite ? 3 : 1), prev};
    }
    if (cur.first == target)
        return;
    if (need_update)
    {
        if (CanPass(maze, cur.first, cur.second))
            DSF(maze, {cur.first.GetNeibor(cur.second), cur.second}, cur, target, data);
        for (auto const & dir: AllDirections())
            if (CanPass(maze, cur.first, dir))
                DSF(maze, {cur.first.GetNeibor(dir), dir}, cur, target, data);
    }
}

//void PrintMap(TMap const & mp, std::map<Cell, pair<int, Cell>> const & data)
//{
//    for (size_t y = 0; y < mp[0].size(); ++y)
//    {
//        for (size_t x = 0; x < mp.size(); ++x)
//        {
//            if (mp[x][y] == 0)
//                cout << "0";
//            else
//            {
//                //                cout << ".";
//                if (data.count(Cell(x,y)) == 1)
//                    cout << "+";
//                else
//                    cout << ".";
//                
//            }
//        }
//        cout << endl;
//    }
//    cout << endl;
//    
//}

vector<Cell> GetClosestPath(const model::World& world,
                            Cell const & start, Direction const start_dir, Cell const & finish)
{
    MapT data;
    DSF(world.getTilesXY(), {start, start_dir}, {start, start_dir}, finish, data);
    //    PrintMap(world.getTilesXY(), data);
    
    vector<Cell> res;
    int const INF = 1000000;
    int best = INF;
    MapKeyT cur = {finish, LEFT};
    for (auto dir: AllDirections())
    {
        if (data.count({finish,dir}) == 0)
            continue;
        if (data[{finish,dir}].first < best)
        {
            best = data[{finish,dir}].first;
            cur = {finish,dir};
        }
        
    }
    if (best == INF)
        return res;
    
    
    while (cur.first != start)
    {
        res.push_back(cur.first);
        cur = data[cur].second;
    }
    res.push_back(start);
    reverse(res.begin(), res.end());
    return res;
}


bool IsStraight(Car const & car, std::vector<Cell> const & path, int N, Game const & game, World const & world)
{
    bool bStrait = false;
    if (path.size() >= N + 1)
    {
        double target4X = (path[N].m_x + 0.5) * game.getTrackTileSize();
        double target4Y = (path[N].m_y + 0.5) * game.getTrackTileSize();
        if (car.getAngleTo(target4X, target4Y) < 20*PI/180)
        {
            bStrait = true;
            TileType curType = GetCellType(world.getTilesXY(), GetCell(car, game));
            for (size_t i =1; i < N; ++i)
                if (curType != GetCellType(world.getTilesXY(), path[i]))
                    bStrait = false;
        }
    }
    return bStrait;
}


int GetStraightLength(std::vector<Cell> const & path)
{
    if (path.empty())
        return 0;
    int res = 0;
    for (auto dir: AllDirections())
    {
        auto cur = path[0];
        int i = 0;
        while (cur == path[i])
        {
            i++;
            switch (dir) {
                case LEFT:
                    cur.m_x--;
                    break;
                case RIGHT:
                    cur.m_x++;
                    break;
                case UP:
                    cur.m_y--;
                    break;
                case DOWN:
                    cur.m_y++;
                    break;
            }
        }
        res = max(res, i);
    }
    return res;
}

bool IsOnPath(Unit const & unit, std::vector<Cell> const & path, Game const & game)
{
    auto targetCell = GetCell(unit, game);
    for (auto const & cell: path)
    {
        if (targetCell == cell)
            return true;
    }
    return false;
}

bool Is180Turn(std::vector<Cell> const & path)
{
    if (path.size()< 4)
        return false;
    for (auto dir: AllDirections())
        if (path[0].GetNeibor(dir) == path[3])
            return true;
    return false;
}




