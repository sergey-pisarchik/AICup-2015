#include "MyStrategy.h"
#include "CommonDefines.h"
#include "Cell.h"
#include "PathUtils.h"
#include "DebugFunctions.h"

using namespace std;

void MyStrategy::move(const Car& self, const World& world, const Game& game, Move& move) {
#ifdef LOG
    if(world.getTick() == 1)
        PrintMap(world.getTilesXY());
#endif
    //    move.setEnginePower(1.0);
    //    move.setThrowProjectile(true);
    //    move.setSpillOil(true);
    
    //    if (world.getTick() > game.getInitialFreezeDurationTicks()) {
    //        move.setUseNitro(true);
    //    }
    
    auto wp = world.getWaypoints();
    
    Cell finish = {self.getNextWaypointX(), self.getNextWaypointY()};
    Cell start = GetCell(self.getX(), self.getY(), game);
    
    vector<Cell> path = GetClosestPath(world, start, finish);
    
    start = finish;
    auto nextWaypointIndex = self.getNextWaypointIndex() + 1;
    if (nextWaypointIndex >= world.getWaypoints().size())
        nextWaypointIndex = 0;
    finish = {world.getWaypoints()[nextWaypointIndex][0], world.getWaypoints()[nextWaypointIndex][1]};
    vector<Cell> nextPath = GetClosestPath(world, start, finish);
    for (size_t i = 1; i < nextPath.size(); ++i)
        path.push_back(nextPath[i]);
    
#ifdef LOG
    cout << "s " << start << " f " << finish << " path ";
    for (auto cell: path)
        cout << cell << " : ";
    cout << " target " << path[1] << endl;
#endif
    
    while (path.size() < 3)
        path.push_back(path.back());
    
    Cell nextTarget = path[2];
    
    double nextWaypointX = (nextTarget.m_x + 0.5) * game.getTrackTileSize();
    double nextWaypointY = (nextTarget.m_y + 0.5) * game.getTrackTileSize();
    
    double cornerTileOffset = 0.25 * game.getTrackTileSize();
    
    switch (GetCellType(world.getTilesXY(), nextTarget))
    {
        case LEFT_TOP_CORNER:
            nextWaypointX += cornerTileOffset;
            nextWaypointY += cornerTileOffset;
            break;
        case RIGHT_TOP_CORNER:
            nextWaypointX -= cornerTileOffset;
            nextWaypointY += cornerTileOffset;
            break;
        case LEFT_BOTTOM_CORNER:
            nextWaypointX += cornerTileOffset;
            nextWaypointY -= cornerTileOffset;
            break;
        case RIGHT_BOTTOM_CORNER:
            nextWaypointX -= cornerTileOffset;
            nextWaypointY -= cornerTileOffset;
            break;
    }
    
    double angleToWaypoint = self.getAngleTo(nextWaypointX, nextWaypointY);
    double speedModule = hypot(self.getSpeedX(), self.getSpeedY());
    
    move.setWheelTurn(angleToWaypoint * 32.0 / PI);
    move.setEnginePower(0.75);
    
    //            if (speedModule * speedModule * abs(angleToWaypoint) > 2.5 * 2.5 * PI)
    //            {
    //                move.setBrake(true);
    //            }

}

MyStrategy::MyStrategy() { }
