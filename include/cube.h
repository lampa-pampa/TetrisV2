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
    bool is_ghost;

    friend std::ostream& operator<<(std::ostream& os, const Cube& cube)
    {
        return os << "{" << cube.position.x << ", " << cube.position.y
            << ", " << cube.color_code << "}";  
    }

    Cube(int x, int y, int color_code, bool is_ghost)
    :
        position{x, y},
        color_code{color_code},
        is_ghost{is_ghost}
    {}

    Cube(int x, int y, int color_code)
    :
        Cube{x, y, color_code, false}
    {}

    Cube(int x, int y)
    :
        Cube{x, y, 0, false}
    {}

    bool operator==(const Cube& other) const
    {
        return this->position == other.position
            and this->is_ghost == other.is_ghost
            and this->color_code == other.color_code;
    }

    bool empty() const
    {
        return this->color_code == 0;
    }

    void clear()
    {
        this->color_code = 0;
        this->is_ghost = false;
    }
};

}

#endif