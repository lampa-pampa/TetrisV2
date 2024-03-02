#ifndef INCLUDE_BRICKS_SOURCE_H
#define INCLUDE_BRICKS_SOURCE_H

#include <vector>

#include "brick.h"

namespace Tetris
{

const std::vector<Brick> bricks_source
{
    {{ {-1, 0}, {0, 0}, {1, 0}, {2, 0} }, true},
    {{ {0, 0}, {1, 0}, {0, 1}, {1, 1} }, true},
    {{ {-1, 0}, {0, 0}, {0, 1}, {1, 1} }},
    {{ {0, 0}, {1, 0}, {-1, 1}, {0, 1} }},
    {{ {-1, 0}, {0, 0}, {1, 0}, {-1, 1} }},
    {{ {-1, 0}, {0, 0}, {1, 0}, {1, 1} }},
    {{ {-1, 0}, {0, 0}, {1, 0}, {0, 1} }},
};

}

#endif