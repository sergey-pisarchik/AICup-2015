#ifndef PATHUTILS
#define PATHUTILS

#include "CommonDefines.h"
#include "Cell.h"


vector<Cell> GetClosestPath(const model::World& world,
                              Cell const & start, Cell const & finish);
TileType GetCellType(TMap const & map, Cell const & cell);

#endif // PATHUTILS

