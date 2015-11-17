
#include "CommonDefines.h"

vector<Direction> const &  AllDirections()
{
    static vector<Direction> res = {LEFT, RIGHT, UP, DOWN};
    return res;
}

