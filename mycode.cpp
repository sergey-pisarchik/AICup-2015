#include "MyCode.h"

using namespace model;
using namespace std;

void f(const Car& self, const World& world, const Game& game, Move& move)
{
    move.setEnginePower(1.0);
    move.setThrowProjectile(true);
    move.setSpillOil(true);

    if (world.getTick() > game.getInitialFreezeDurationTicks()) {
        move.setUseNitro(true);
    }
}