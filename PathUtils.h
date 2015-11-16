#ifndef PATHUTILS
#define PATHUTILS

#include <CommonDefines.h>


std::vector<Cell> GetClosestPath(const model::World& world, Cell start, Cell finish);
TileType GetCellType(TMap const & map, Cell const & cell);

#endif // PATHUTILS

