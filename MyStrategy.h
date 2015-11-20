#pragma once

#ifndef _MY_STRATEGY_H_
#define _MY_STRATEGY_H_

#include "Strategy.h"
#include "Strategy.h"
#include "CommonDefines.h"
#include "Cell.h"

class MyStrategy : public Strategy {
public:
    MyStrategy();
    
    void move(const model::Car& self, const model::World& world,
              const model::Game& game, model::Move& move);
    void BackwardMove(const model::Car& self, const model::World& world,
                      const model::Game& game, model::Move& move);
private:
    double m_dPrevSpeed = -1;
    int m_BacwardTick = -1;
    int m_ForvardTick = -1;
    double m_BackwardWheelAngle = -1;
    bool m_bBackwardMove = false;
    std::vector<Cell> m_visitedCells;
};



#endif
