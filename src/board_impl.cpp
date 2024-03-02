#include "board_impl.h"

#include <cassert>
#include <vector>

#include <boost/range/irange.hpp>

#include "brick.h"
#include "cube.h"
#include "vector_2.h"

namespace Tetris
{

using std::vector;
using boost::irange;

vector<Brick> BoardImpl::find_lines_in_range(int from_y, int to_y) const
{
    vector<Brick> lines;
    for (const auto& y : irange(from_y, to_y + 1))
    {
        Brick line{};
        bool is_full_line{true};
        for (const auto& x : irange(this->width))
        {
            const Cube& cube{this->cubes[y][x]};
            if (cube.empty())
            {
                is_full_line = false;
                break;
            }
            line.cubes.push_back(cube);
        }
        if (is_full_line)
            lines.emplace_back(std::move(line));
    }
    return lines;
}

void BoardImpl::compress(int start_y)
{
    for (const auto& y : irange(start_y, 0, -1))
    {
        for (const auto& x : irange(this->width))
        {
            this->cubes[y][x] = this->cubes[y - 1][x];
            this->cubes[y][x].coords = {x, y};
        }
    }
    for (const auto& x : irange(this->width))
        this->cubes[0][x].clear();
}

BoardImpl::BoardImpl(int width, int height)
:
    width(width),
    height(height)
{
    for (const auto& y : irange(height))
    {
        vector<Cube> row;
        for (const auto& x : irange(width))
            row.emplace_back(Cube{x, y});
        this->cubes.emplace_back(std::move(row));
    }
}

bool BoardImpl::is_space_for_brick(const Brick& brick) const 
{
    for (const auto& cube : brick.cubes)
    {
        if (not this->position_is_in_range(cube.coords)
            or not this->cubes[cube.coords.y][cube.coords.x].empty())
            return false;
    }
    return true;
}

void BoardImpl::put_cubes(const vector<Cube>& cubes)
{
    for (const auto& cube : cubes)
    {
        assert(this->position_is_in_range(cube.coords));
        this->cubes[cube.coords.y][cube.coords.x] = cube;
    }
}

void BoardImpl::clear_cubes(const vector<Cube>& cubes)
{
    for (const auto& cube : cubes)
    {
        assert(this->position_is_in_range(cube.coords));
        this->cubes[cube.coords.y][cube.coords.x].clear();
    }
}

int BoardImpl::remove_lines_in_range_and_compress(int from_y, int to_y)
{
    const vector lines{this->find_lines_in_range(from_y, to_y)};
    for (const auto& line : lines)
    {
        this->clear_cubes(line.cubes);
        this->compress(line.cubes[0].coords.y);
    }
    return lines.size();
}

}