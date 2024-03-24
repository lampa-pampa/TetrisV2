#ifndef INCLUDE_CUBE_H
#define INCLUDE_CUBE_H

#include <cstdint>
#include <ostream>

#include "vector_2.h"

namespace Tetris
{

struct Cube final
{
    Vector2 position;
    uint_fast8_t color_id;

    friend std::ostream& operator<<(std::ostream& os, const Cube& cube)
    {
        return os << "{" << cube.position.x << ", " << cube.position.y
            << ", " << cube.color_id << "}";
    }

    Cube(int x, int y, uint_fast8_t color_id = 0)
    :
        position{x, y},
        color_id{color_id}
    {}

    bool operator==(const Cube& other) const
    {
        return position == other.position
            and color_id == other.color_id;
    }

    void clear()
    {
        color_id = 0;
    }

    bool empty() const
    {
        return color_id == 0;
    }
};

}

#endif