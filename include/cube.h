#ifndef INCLUDE_CUBE_H
#define INCLUDE_CUBE_H

#include <ostream>

#include "vector_2.h"

namespace Tetris
{

struct Cube final
{
    friend std::ostream& operator<<(std::ostream& os, const Cube& cube)
    {
        return os << "{" << cube.position.x << ", " << cube.position.y
            << ", " << cube.color_code << "}";
    }

    static constexpr int black_color_code{0};

    Vector2 position;
    int color_code;

    Cube(int x, int y, int color_code)
    :
        position{x, y},
        color_code{color_code}
    {}

    Cube(int x, int y)
    :
        Cube{x, y, black_color_code}
    {}

    bool operator==(const Cube& other) const
    {
        return this->position == other.position
            and this->color_code == other.color_code;
    }

    void clear()
    {
        this->color_code = black_color_code;
    }

    bool empty() const
    {
        return this->color_code == black_color_code;
    }
};

}

#endif