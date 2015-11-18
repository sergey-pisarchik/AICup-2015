#include "MyCode.h"


#include "CommonDefines.h"
#include "Cell.h"
#include "PathUtils.h"
#include "DebugFunctions.h"

using namespace std;



void f(const Car& self, const World& world, const Game& game, Move& move)
{
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

    Cell finish = {self.getNextWaypointX(), self.getNextWaypointY()};
    Cell start = GetCell(self.getX(), self.getY(), game);

    vector<Cell> path = GetClosestPath(world, start, finish);
#ifdef LOG
    cout << "s " << start << " f " << finish << " path ";
    for (auto cell: path)
        cout << cell << " : ";
    cout << " target " << path[1] << endl;
#endif
    
    while (path.size() < 2)
        path.push_back(path.back());

    double nextWaypointX = (path[1].m_x + 0.5) * game.getTrackTileSize();
    double nextWaypointY = (path[1].m_y + 0.5) * game.getTrackTileSize();

            double cornerTileOffset = 0.25 * game.getTrackTileSize();

            switch (world.getTilesXY()[self.getNextWaypointX()][self.getNextWaypointY()])
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
