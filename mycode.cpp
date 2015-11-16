#include "MyCode.h"



#include <cmath>
#include <cstdlib>
#include <math.h>
#include <iostream>

using namespace model;
using namespace std;

#define PI 3.14159265358979323846
#define _USE_MATH_DEFINES

void f(const Car& self, const World& world, const Game& game, Move& move)
{
//    move.setEnginePower(1.0);
//    move.setThrowProjectile(true);
//    move.setSpillOil(true);

//    if (world.getTick() > game.getInitialFreezeDurationTicks()) {
//        move.setUseNitro(true);
//    }

    double nextWaypointX = (self.getNextWaypointX() + 0.5) * game.getTrackTileSize();
            double nextWaypointY = (self.getNextWaypointY() + 0.5) * game.getTrackTileSize();

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

            if (speedModule * speedModule * abs(angleToWaypoint) > 2.5 * 2.5 * PI)
            {
                move.setBrake(true);
            }
}
