#include "MyStrategy.h"
#include "mycode.h"

#define PI 3.14159265358979323846
#define _USE_MATH_DEFINES

#include <cmath>
#include <cstdlib>

using namespace model;
using namespace std;

void MyStrategy::move(const Car& self, const World& world, const Game& game, Move& move) {
   f(self, world, game, move);
}

MyStrategy::MyStrategy() { }
