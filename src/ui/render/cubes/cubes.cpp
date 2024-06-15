#include "ui/render/cubes/cubes.h"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <map>
#include <vector>

#include <boost/range/irange.hpp>

#include "brick/brick_name.h"
#include "cube/cube.h"
#include "ui/color/color_name.h"
#include "ui/color/nv_color.h"
#include "ui/render/rectangle.h"
#include "ui/render/sprite.h"
#include "vector2/vector2.h"

using boost::irange;
using std::all_of;
using std::find;
using std::function;
using std::map;
using std::vector;

namespace Tetris::Ui
{

Sprites RenderCubes::render(const vector<Cube>& cubes,
    const map<BrickName, ColorName>& brick_name_to_color_name,
    uint_fast8_t color_value,
    bool fill) const
{
    if (fill)
        return render_filled(cubes, brick_name_to_color_name, color_value);
    else
        return render_outline(cubes, brick_name_to_color_name, color_value);
}

//-----------------------------------------------------------------------

vector<Rectangle> RenderCubes::create_outline(int outline_width) const
{
    const int edge{cube_size_ - 2 * outline_width};
    const int edge_with_corner{outline_width + edge};
    return {
        {{0, 0}, {outline_width}},
        {{outline_width, 0}, {edge, outline_width}},
        {{edge_with_corner, 0}, {outline_width}},
        {{0, outline_width}, {outline_width, edge}},
        {{edge_with_corner, outline_width}, {outline_width, edge}},
        {{0, edge_with_corner}, {outline_width}},
        {{outline_width, edge_with_corner}, {edge, outline_width}},
        {{edge_with_corner, edge_with_corner}, {outline_width}},
    };
}

Sprites RenderCubes::render_filled(const vector<Cube>& cubes,
    const map<BrickName, ColorName>& brick_name_to_color_name,
    uint_fast8_t color_value) const
{
    Sprites sprites{};
    for (const auto& cube : cubes)
        sprites.emplace_back(
            Rectangle{compute_cube_position(cube.position), cube_size_},
            NvColor{brick_name_to_color_name.at(cube.brick_name), color_value});
    return sprites;
}

void RenderCubes::for_each_outline_part(
    const function<void(const Vector2& position_offset,
        const Rectangle& outline_part)>& operation) const
{
    int outline_index{0};
    for (const auto& y : irange(-1, 2))
    {
        for (const auto& x : irange(-1, 2))
        {
            if (x == 0 and y == 0)
                continue;
            operation({x, y}, outline_[outline_index]);
            ++outline_index;
        }
    }
}

Sprites RenderCubes::render_outline(const vector<Cube>& cubes,
    const map<BrickName, ColorName>& brick_name_to_color_name,
    uint_fast8_t color_value) const
{
    Sprites sprites{};
    for (const auto& cube : cubes)
    {
        const NvColor color{
            brick_name_to_color_name.at(cube.brick_name), color_value};
        const Vector2 cube_position{compute_cube_position(cube.position)};

        for_each_outline_part(
            [&](const Vector2& position_offset, const Rectangle& outline_part)
            {
                if (outline_part_should_be_added(cubes, cube, position_offset))
                {
                    const Vector2 outline_position{
                        cube_position + outline_part.position};
                    sprites.emplace_back(
                        Rectangle{outline_position, outline_part.size}, color);
                }
            });
    }
    return sprites;
}

bool RenderCubes::outline_part_should_be_added(const std::vector<Cube>& cubes,
    const Cube& cube,
    const Vector2& position_offset) const
{
    if (position_offset.x == 0 or position_offset.y == 0)
        return outline_edge_should_be_added(cubes, cube, position_offset);
    return outline_corner_should_be_added(cubes, cube, position_offset);
}

bool RenderCubes::outline_edge_should_be_added(const std::vector<Cube>& cubes,
    const Cube& cube,
    const Vector2& position_offset) const
{
    return find(cubes.begin(),
               cubes.end(),
               Cube{cube.position + position_offset, cube.brick_name})
        == cubes.end();
}

vector<Cube> RenderCubes::create_corner_neighbours(
    const Cube& cube, const Vector2& position_offset) const
{
    return {
        Cube{cube.position + position_offset, cube.brick_name},
        Cube{cube.position + Vector2{position_offset.x, 0}, cube.brick_name},
        Cube{cube.position + Vector2{0, position_offset.y}, cube.brick_name},
    };
}

bool RenderCubes::outline_corner_should_be_added(const std::vector<Cube>& cubes,
    const Cube& cube,
    const Vector2& position_offset) const
{
    const vector<Cube> neighbour_cubes{
        create_corner_neighbours(cube, position_offset)};
    return not all_of(neighbour_cubes.begin(),
        neighbour_cubes.end(),
        [&cubes](const Cube& cube)
        { return find(cubes.begin(), cubes.end(), cube) != cubes.end(); });
}

} // namespace Tetris::Ui
