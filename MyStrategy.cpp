#include "MyStrategy.h"
#include "MyCode.h"

void MyStrategy::move(const Car& self, const World& world, const Game& game, Move& move) {
   f(self, world, game, move);
}

MyStrategy::MyStrategy() { }
