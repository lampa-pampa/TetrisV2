#include "brick/brick.h"

#include <algorithm>
#include <ostream>
#include <vector>

#include <boost/range/irange.hpp>

#include "cube/cube.h"
#include "vector_2/vector_2.h"

using boost::irange;
using std::max_element;
using std::min_element;
using std::ostream;
using std::swap;
using std::vector;

namespace Tetris
{

Brick Brick::get_translated(const Brick& brick, Vector2 position)
{
    Brick translated_brick{brick};
    for (auto& cube_position : translated_brick.cube_positions)
        cube_position += position;
    return translated_brick;
}

Vector2 Brick::get_rotated_position(
    Vector2 position, Vector2 rotation_offset, int quarters_rotation)
{
    for (const auto& i : irange(quarters_rotation))
    {
        swap(position.x, position.y);
        position.x *= -1;
        position += rotation_offset;
    }
    return position;
}

Brick Brick::get_rotated(const Brick& brick, int quarters_rotation)
{
    Brick rotated_brick{brick};
    for (auto& cube_position : rotated_brick.cube_positions)
    {
        cube_position = get_rotated_position(
            cube_position, brick.rotation_offset, quarters_rotation);
    }
    return rotated_brick;
}

vector<Cube> Brick::get_cubes() const
{
    vector<Cube> cubes{};
    for (const auto& cube_position : cube_positions)
        cubes.emplace_back(cube_position.x, cube_position.y, name);
    return cubes;
}

int Brick::get_min_x() const
{
    if (cube_positions.empty())
        return 0;
    return min_element(cube_positions.begin(),
        cube_positions.end(),
        [](const Vector2& a, const Vector2& b) { return a.x < b.x; })
        ->x;
}

int Brick::get_max_x() const
{
    if (cube_positions.empty())
        return 0;
    return max_element(cube_positions.begin(),
        cube_positions.end(),
        [](const Vector2& a, const Vector2& b) { return a.x < b.x; })
        ->x;
}

int Brick::get_min_y() const
{
    if (cube_positions.empty())
        return 0;
    return min_element(cube_positions.begin(),
        cube_positions.end(),
        [](const Vector2& a, const Vector2& b) { return a.y < b.y; })
        ->y;
}

int Brick::get_max_y() const
{
    if (cube_positions.empty())
        return 0;
    return max_element(cube_positions.begin(),
        cube_positions.end(),
        [](const Vector2& a, const Vector2& b) { return a.y < b.y; })
        ->y;
}

Vector2 Brick::get_size() const
{
    if (empty())
        return {};
    return {get_max_x() - get_min_x() + 1, get_max_y() - get_min_y() + 1};
}

ostream& operator<<(ostream& os, const vector<Vector2>& cube_positions)
{
    for (const auto& cube_position : cube_positions)
    {
        os << cube_position;
        if (&cube_position != &cube_positions.back())
            os << ", ";
    }
    return os;
}

} // namespace Tetris
