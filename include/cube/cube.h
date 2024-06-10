#ifndef INCLUDE_CUBE_H
#define INCLUDE_CUBE_H

#include <ostream>

#include "brick/brick_name.h"
#include "vector_2/vector_2.h"

namespace Tetris
{

struct Cube final
{
    Vector2 position;
    BrickName brick_name;

    friend std::ostream& operator<<(std::ostream& os, const Cube& cube)
    {
        return os << "{" << cube.position.x << ", " << cube.position.y << ", "
                  << cube.brick_name << "}";
    }

    Cube(int x, int y, BrickName brick_name = BrickName::empty)
      : position{x, y},
        brick_name{brick_name}
    {}

    bool operator==(const Cube& other) const
    {
        return position == other.position and brick_name == other.brick_name;
    }

    void clear()
    {
        brick_name = BrickName::empty;
    }

    bool empty() const
    {
        return brick_name == BrickName::empty;
    }
};

} // namespace Tetris

#endif
