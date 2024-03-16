#ifndef INCLUDE_CUBE_H
#define INCLUDE_CUBE_H

#include <ostream>

#include "vector_2.h"

namespace Tetris
{

struct Cube final
{
    Vector2 position;
    int color_code;

    friend std::ostream& operator<<(std::ostream& os, const Cube& cube)
    {
        return os << "{" << cube.position.x << ", " << cube.position.y
            << ", " << cube.color_code << "}";
    }

    Cube(int x, int y, int color_code)
    :
        position{x, y},
        color_code{color_code}
    {}

    Cube(int x, int y)
    :
        Cube{x, y, 0}
    {}

    bool operator==(const Cube& other) const
    {
        return this->position == other.position
            and this->color_code == other.color_code;
    }

    void clear()
    {
        this->color_code = 0;
    }

    bool empty() const
    {
        return this->color_code == 0;
    }
};

}

#endif