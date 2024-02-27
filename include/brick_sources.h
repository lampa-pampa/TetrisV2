#ifndef BRICK_SOURCES_H
#define BRICK_SOURCES_H

#include "brick.h"
#include <vector>

const std::vector<Brick> brick_sources
{
    {{ {-1, 0}, {0, 0}, {1, 0}, {2, 0} }, true},
    {{ {0, 0}, {1, 0}, {0, 1}, {1, 1} }, true},
    {{ {-1, 0}, {0, 0}, {0, 1}, {1, 1} }},
    {{ {0, 0}, {1, 0}, {-1, 1}, {0, 1} }},
    {{ {-1, 0}, {0, 0}, {1, 0}, {-1, 1} }},
    {{ {-1, 0}, {0, 0}, {1, 0}, {1, 1} }},
    {{ {-1, 0}, {0, 0}, {1, 0}, {0, 1} }},
};

#endif