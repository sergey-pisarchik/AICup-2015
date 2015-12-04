#include "MyStrategy.h"
#include "CommonDefines.h"
#include "Cell.h"
#include "PathUtils.h"
#include "DebugFunctions.h"
#include "UsefullFunctions.h"

using namespace std;

int const BACWARD_DUR = 150;

void MyStrategy::move(const Car& self, const World& world, const Game& game, Move& move)
{
    auto curCell = GetCell(self.getX(), self.getY(), game);
    
    if (m_visitedCells.empty() || m_visitedCells.back() != curCell)
        m_visitedCells.push_back(curCell);
    
    
#ifdef LOG
    if(world.getTick() == 1)
        PrintMap(world.getTilesXY());
#endif
    //        move.setEnginePower(1.0);
    
    ////////
    // FIRE & OIL
    ///////
    
    for (Car const & car: world.getCars())
    {
        if (car.isTeammate())
            continue;
        if (car.getDurability() == 0)
            continue;
        double dAngleDeg = FDeg(self.getAngleTo(car));
        double dist = self.getDistanceTo(car);
        if (dAngleDeg < 5
            && dist < 1.9 * game.getTrackTileSize())
            move.setThrowProjectile(true);
        
//        for (double tick = 0; tick < 5. * 800./60.; tick += 0.1)
//        {
//            auto car_pos = GetPosition(car, tick);
//            auto bullet_pos_x = GetBulletPosition(self, tick);
//            if (GetDist(car_pos.first, car_pos.second, bullet_pos_x.first, bullet_pos_x.second) < 20)
//                move.setThrowProjectile(true);
//        }
        
        
        for (int i = 3; i < 7 && i < m_visitedCells.size(); ++i)
        {
            auto carCell = GetCell(car, game);
            if (carCell == m_visitedCells[m_visitedCells.size() - i])
                move.setSpillOil(true);
        }
    }
    
    ////////
    //BACKBARD
    ////////
    
    if (m_bBackwardMove)
        return BackwardMove(self, world, game, move);

    
    /////////
    // PATH
    /////////
    
    
    Cell finish = {self.getNextWaypointX(), self.getNextWaypointY()};
    Cell start = curCell;

    vector<Cell> path = GetClosestPath(world, start, GetDirection(self), finish, game);
    
    Cell start2 = finish;
    auto nextWaypointIndex = self.getNextWaypointIndex() + 1;
    if (nextWaypointIndex >= world.getWaypoints().size())
        nextWaypointIndex = 0;
    
    Direction nextDir = GetDirection(self);
    if (path.size() >= 2)
    {
        nextDir = GetDirection(path[path.size() - 2], path.back());
    }
    Cell finish2 = {world.getWaypoints()[nextWaypointIndex][0], world.getWaypoints()[nextWaypointIndex][1]};
    vector<Cell> nextPath = GetClosestPath(world, start2, nextDir, finish2, game);
    for (size_t i = 1; i < nextPath.size(); ++i)
        path.push_back(nextPath[i]);
    
    
    if (path.empty())
        path.push_back({0,0});
    while (path.size() < 3)
        path.push_back(path.back());
    
    
    ////////
    // TARGET CELL
    ////////
    
    
    Cell nextTarget = path[1];
    Cell nextTarget2 = path[2];
    
#ifdef LOG
    cout << "s " << start << " wp " << finish <<  " wp2 " << finish << endl << "path ";
    for (auto cell: path)
        cout << cell << " : ";
    cout << " target " << nextTarget << endl;
#endif
    
    
    double nextWaypointX = (nextTarget.m_x + 0.5) * game.getTrackTileSize();
    double nextWaypointY = (nextTarget.m_y + 0.5) * game.getTrackTileSize();
    
    double nextWaypointX2 = (nextTarget2.m_x + 0.5) * game.getTrackTileSize();
    double nextWaypointY2 = (nextTarget2.m_y + 0.5) * game.getTrackTileSize();
    
    
    
    
    double k = 0.4;
    nextWaypointX = (k*nextWaypointX + (1-k)*nextWaypointX2);
    nextWaypointY = (k*nextWaypointY + (1-k)*nextWaypointY2);
    
    
    
    
    //    double cornerTileOffset = 0.15 * game.getTrackTileSize();
    
    ///////////
    //// BONUS
    ///////////
    
    
    int strightLength = GetStraightLength(path);
    double min_bonus_dist = (strightLength - 1.5 ) * game.getTrackTileSize();
    if (strightLength > 2)
    {
        for (auto const & bonus: world.getBonuses())
        {
            if (FDeg(self.getAngleTo(bonus)) < 15)
            {
                if (self.getDistanceTo(bonus) < min_bonus_dist && IsOnPath(bonus, path, game, strightLength))
                {
                    min_bonus_dist = self.getDistanceTo(bonus);
                    nextWaypointX = bonus.getX();
                    nextWaypointY = bonus.getY();
                }
            }
            
        }
    }
    
    min_bonus_dist += 300;

    for (auto const & bonus: world.getBonuses())
    {
        if ((bonus.getType() == PURE_SCORE || (bonus.getType() == REPAIR_KIT && self.getDurability() < 0.5 ))
            && self.getDistanceTo(bonus) < min_bonus_dist
            && IsOnPath(bonus, path, game, 2)
            && FDeg(self.getAngleTo(bonus)) < 25)
        {
            min_bonus_dist = self.getDistanceTo(bonus);
            nextWaypointX = bonus.getX();
            nextWaypointY = bonus.getY();
        }
        
    }
    
    
    //////////
    // corner
    //////////
    
    
    for (int i = 0; i< 4; ++i)
    {
        auto corener_coords = GetCornerCoords(curCell, i, game);
        if (FDeg(self.getAngleTo(corener_coords.first, corener_coords.second)) < 15)
        {
            nextWaypointX = (nextTarget.m_x + 0.5) * game.getTrackTileSize();
            nextWaypointY = (nextTarget.m_y + 0.5) * game.getTrackTileSize();
        }
    }
    
    
    
    ///////////
    // WHEEL
    //////////
    double angleToWaypoint = self.getAngleTo(nextWaypointX, nextWaypointY);
    //    move.setWheelTurn(angleToWaypoint * 32.0 / PI);
    
    double MAX_ANGLE = 32.;
    
    double Wheel_turn = 0;
    if (FDeg(angleToWaypoint) > MAX_ANGLE)
        Wheel_turn = (angleToWaypoint > 0 ? 1 : -1);
    else
        Wheel_turn = ((1./MAX_ANGLE)*(1.15 * Deg(angleToWaypoint)));
    
    move.setWheelTurn(Wheel_turn);

    
    if (world.getTick() < 205)
        move.setEnginePower(0.25);
    else
        move.setEnginePower(1);
    
    //////////
    /// NITRO
    //////////
    
    int straight_length = GetStraightLength(path);
    if (straight_length > 6 && world.getTick() > 220)
    {
        if (FDeg(angleToWaypoint) < 20)
            move.setUseNitro(true);
    }
    
    if (self.getRemainingNitroTicks() == 1 && strightLength < 2)
        m_brakeAfteNitroTicks = 45;
    m_brakeAfteNitroTicks--;
    if (m_brakeAfteNitroTicks > 0)
        move.setBrake(true);
    
    if (strightLength < 5  && (FDeg(angleToWaypoint) > 15 && Speed(self) > 15))
    {
        move.setBrake(true);
    }
    
    
    
    
    //////////
    // 180 turn
    //////////
    
    if (Is180Turn(path))
    {
        m_180TurnCurCell = path[0];
        m_180TurnMode = true;
        m_180TurnLength = 3;
    }
    
    if (m_180TurnMode && curCell != m_180TurnCurCell)
    {
        m_180TurnLength--;
        if (m_180TurnLength == 0)
            m_180TurnMode = false;
        m_180TurnCurCell = curCell;
    }
    
    if (m_180TurnMode && Speed(self) > 12)
    {
        move.setBrake(true);
    }
    
    
    //            if (speedModule * speedModule * abs(angleToWaypoint) > 2.5 * 2.5 * PI)
    //            {
    //                move.setBrake(true);
    //            }
    
    
    ////////
    ///
    ///////
    m_ForvardTick++;
    
    
    double speedModule = hypot(self.getSpeedX(), self.getSpeedY());
    
    
    if (m_ForvardTick > 30 && world.getTick() > 230)
        if (speedModule < 1e-1 && m_dPrevSpeed < 1e-1)
        {
            m_bBackwardMove = true;
            m_BacwardTick = BACWARD_DUR;
            m_BackwardWheelAngle = -Wheel_turn;
            return BackwardMove(self, world, game, move);
        }
    m_dPrevSpeed = speedModule;
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
        {
            move.setEnginePower(1);
            move.setWheelTurn(m_BackwardWheelAngle);
            
        }
        else
            move.setWheelTurn(m_BackwardWheelAngle);
        if (m_BacwardTick < BACWARD_DUR / 6)
        {
            move.setBrake(true);
            move.setWheelTurn(0);
        }
        
    }
}

MyStrategy::MyStrategy() { }
