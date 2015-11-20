#ifndef COMMONDEFINES
#define COMMONDEFINES

#define PI 3.14159265358979323846
#define _USE_MATH_DEFINES

#include <cmath>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

#include "model/Bonus.h"
#include "model/Car.h"
#include "model/CarType.h"
#include "model/BonusType.h"
#include "model/Game.h"
#include "model/Move.h"
#include "model/World.h"
#include "model/Player.h"
#include "model/Direction.h"

using namespace model;
using namespace std;
#define LOG


std::vector<Direction> const &  AllDirections();

typedef std::vector<std::vector<TileType> > TMap;

#endif // COMMONDEFINES

