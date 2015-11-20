#ifndef PATHUTILS
#define PATHUTILS

#include "CommonDefines.h"
#include "Cell.h"


vector<Cell> GetClosestPath(const model::World& world,
                              Cell const & start, Cell const & finish);
TileType GetCellType(TMap const & map, Cell const & cell);

bool IsStraight(Car const & car, std::vector<Cell> const & path, int N, Game const & game, World const & world);
int GetStraightLength(std::vector<Cell> const & path);

bool IsOnPath(Unit const & unit, std::vector<Cell> const & path, Game const & game);

#endif // PATHUTILS

