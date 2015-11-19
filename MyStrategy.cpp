#include "MyStrategy.h"
#include "CommonDefines.h"
#include "Cell.h"
#include "PathUtils.h"
#include "DebugFunctions.h"

using namespace std;

int const BACWARD_DUR = 65;

void MyStrategy::move(const Car& self, const World& world, const Game& game, Move& move)
{

#ifdef LOG
    if(world.getTick() == 1)
        PrintMap(world.getTilesXY());
#endif
//        move.setEnginePower(1.0);
        move.setThrowProjectile(true);
        move.setSpillOil(true);
//        move.setUseNitro(true);

        if (m_bBackwardMove)
            return BackwardMove(self, world, game, move);
        m_ForvardTick++;
        double speedModule = hypot(self.getSpeedX(), self.getSpeedY());


        if (m_ForvardTick > 10 && world.getTick() > 230)
            if (speedModule < 1e-1 && m_dPrevSpeed < 1e-1)
            {
                m_bBackwardMove = true;
                m_BacwardTick = 65;
                m_BackwardWheelAngle = -self.getWheelTurn();
                return BackwardMove(self, world, game, move);
            }
        m_dPrevSpeed = speedModule;
    
    //    if (world.getTick() > game.getInitialFreezeDurationTicks()) {
    //        move.setUseNitro(true);
    //    }
    

    
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
    
    if (path.empty())
        path.push_back({0,0});
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

    
    move.setWheelTurn(angleToWaypoint * 32.0 / PI);
//    move.setWheelTurn(1);
    move.setEnginePower(0.75);
    
    //            if (speedModule * speedModule * abs(angleToWaypoint) > 2.5 * 2.5 * PI)
    //            {
    //                move.setBrake(true);
    //            }

}


void MyStrategy::BackwardMove(const model::Car& self, const model::World& world,
                  const model::Game& game, model::Move& move)
{
    m_BacwardTick--;
    if (m_BacwardTick < 0)
    {
        m_bBackwardMove = false;
        move.setEnginePower(0.75);
        move.setWheelTurn(0);
        m_ForvardTick = 0;
    }
    else
    {
         move.setEnginePower(-1);
         if (m_BacwardTick < BACWARD_DUR / 3)
             move.setWheelTurn(0);
         else
            move.setWheelTurn(m_BackwardWheelAngle);
    }
}

MyStrategy::MyStrategy() { }
