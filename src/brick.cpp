#include "brick.h"

#include <algorithm>
#include <ostream>

#include <boost/range/irange.hpp>

#include "cube.h"
#include "vector_2.h"

namespace Tetris
{

using std::swap;
using std::ostream;
using boost::irange;

Brick Brick::get_colored(const Brick& brick, int color_code)
{
    Brick colored_brick{brick};
    for (auto& cube : colored_brick.cubes)
        cube.color_code = color_code;
    return colored_brick;
}

Brick Brick::get_translated(const Brick& brick, Vector2 position)
{
    Brick translated_brick{brick};
    for (auto& cube : translated_brick.cubes)
        cube.position += position;
    return translated_brick;
}

Brick Brick::get_rotated(const Brick& brick, int quarters_rotation)
{
    Brick rotated_brick{brick};
    for (auto& cube : rotated_brick.cubes)
    {
        for (const auto& i : irange(quarters_rotation % rotation_quantity))
        {
            swap(cube.position.x, cube.position.y);
            cube.position.x *= -1;
            cube.position += brick.rotation_offset;
        }
    }
    return rotated_brick;
}

Brick Brick::get_ghostified(const Brick& brick)
{
    Brick ghostified_brick{brick};
    for (auto& cube : ghostified_brick.cubes)
        cube.is_ghost = true;
    return ghostified_brick;
}

ostream& operator<<(ostream& os, const Brick& brick)
{
    os << "{{ ";
    for (const auto& cube : brick.cubes)
    {
        os << cube;
        if (&cube != &brick.cubes.back())
            os << ", ";
    }
    return os << " }, " << brick.rotation_offset << "}";
}

}