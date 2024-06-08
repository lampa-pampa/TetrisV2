#include "board/board_impl.h"

#include <cassert>
#include <vector>

#include <boost/range/irange.hpp>

#include "brick/brick.h"
#include "cube/cube.h"
#include "vector_2/vector_2.h"

using boost::irange;
using std::vector;

namespace Tetris
{

BoardImpl::BoardImpl(Vector2 size): size_{size}
{
    cubes_ = create_cubes();
}

void BoardImpl::put_cubes(const vector<Cube>& cubes)
{
    for (const auto& cube : cubes)
    {
        assert(position_is_in_range(cube.position));
        get_cube(cube.position) = cube;
    }
}

vector<int> BoardImpl::remove_lines_and_compress(int from_y, int to_y)
{
    assert(
        position_is_in_range({0, from_y}) and position_is_in_range({0, to_y}));
    const vector rows{find_rows_with_line(from_y, to_y)};
    for (const auto& y : rows)
        compress(y);
    return rows;
}

bool BoardImpl::brick_is_valid(const Brick& brick) const
{
    for (const auto& cube_position : brick.cube_positions)
    {
        if (not position_is_valid(cube_position))
            return false;
    }
    return true;
}

vector<Cube> BoardImpl::get_visible_brick_cubes(const vector<Cube>& cubes) const
{
    vector<Cube> visible_cubes{};
    for (const auto& cube : cubes)
    {
        if (cube.position.y >= 0)
            visible_cubes.push_back(cube);
    }
    return visible_cubes;
}

//-------------------------------------------------------------

BoardImpl::CubeMatrix BoardImpl::create_cubes() const
{
    CubeMatrix cubes;
    for (const auto& y : irange(size_.y))
    {
        vector<Cube> row{};
        for (const auto& x : irange(size_.x))
            row.emplace_back(x, y);
        cubes.emplace_back(std::move(row));
    }
    return cubes;
}

vector<int> BoardImpl::find_rows_with_line(int from_y, int to_y) const
{
    vector<int> line_positions;
    for (const auto& y : irange(from_y, to_y + 1))
    {
        if (is_row_with_line(y))
            line_positions.push_back(y);
    }
    return line_positions;
}

bool BoardImpl::is_row_with_line(int y) const
{
    for (const auto& cube : cubes_[y])
    {
        if (cube.empty())
            return false;
    }
    return true;
}

Brick BoardImpl::try_to_create_line(int y) const
{
    Brick line{};
    for (const auto& cube : cubes_[y])
    {
        if (cube.empty())
            return {};
        line.cube_positions.push_back(cube.position);
    }
    return line;
}

void BoardImpl::compress(int start_y)
{
    for (const auto& y : irange(start_y, 0, -1))
    {
        for (const auto& x : irange(size_.x))
            copy_cube_above({x, y});
    }
    clear_top_row();
}

} // namespace Tetris
