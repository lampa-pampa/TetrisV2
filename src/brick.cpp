#include "brick.h"

#include <algorithm>
#include <cstdint>
#include <ostream>
#include <vector>

#include <boost/range/irange.hpp>

#include "cube.h"
#include "vector_2.h"

using boost::irange;
using std::max_element;
using std::min_element;
using std::ostream;
using std::swap;
using std::vector;

namespace Tetris
{

Brick Brick::get_colored(const Brick& brick, uint_fast8_t color_id)
{
    Brick colored_brick{brick};
    for (auto& cube : colored_brick.cubes)
        cube.color_id = color_id;
    return colored_brick;
}

Brick Brick::get_translated(const Brick& brick, Vector2 position)
{
    Brick translated_brick{brick};
    for (auto& cube : translated_brick.cubes)
        cube.position += position;
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
    for (auto& cube : rotated_brick.cubes)
    {
        cube.position = get_rotated_position(
            cube.position, brick.rotation_offset, quarters_rotation);
    }
    return rotated_brick;
}

int Brick::get_min_x() const
{
    if (this->cubes.empty())
        return 0;
    return min_element(
        this->cubes.begin(),
        this->cubes.end(),
        [](const Cube& a, const Cube& b){
            return a.position.x < b.position.x;}
    )->position.x;
}

int Brick::get_max_x() const
{
    if (this->cubes.empty())
        return 0;
    return max_element(
        this->cubes.begin(),
        this->cubes.end(),
        [](const Cube& a, const Cube& b){
            return a.position.x < b.position.x;}
    )->position.x;
}

int Brick::get_min_y() const
{
    if (this->cubes.empty())
        return 0;
    return min_element(
        this->cubes.begin(),
        this->cubes.end(),
        [](const Cube& a, const Cube& b){
            return a.position.y < b.position.y;}
    )->position.y;
}

int Brick::get_max_y() const
{
    if (this->cubes.empty())
        return 0;
    return max_element(
        this->cubes.begin(),
        this->cubes.end(),
        [](const Cube& a, const Cube& b){
            return a.position.y < b.position.y;}
    )->position.y;
}

Vector2 Brick::get_size() const
{
    if (this->empty())
        return {};
    return {
        this->get_max_x() - this->get_min_x() + 1,
        this->get_max_y() - this->get_min_y() + 1,
    };
}

ostream& operator<<(ostream& os, const vector<Cube>& cubes)
{
    for (const auto& cube : cubes)
    {
        os << cube;
        if (&cube != &cubes.back())
            os << ", ";
    }
    return os;
}

}