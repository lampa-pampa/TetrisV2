#include "ui/render/cubes/cubes.h"

#include <cstdint>
#include <map>
#include <vector>

#include "brick/brick_name.h"
#include "cube/cube.h"
#include "ui/color/color_name.h"
#include "ui/render/rectangle.h"
#include "ui/render/sprite.h"
#include "vector_2/vector_2.h"

using std::map;
using std::vector;

namespace Tetris::Ui
{

Sprites RenderCubes::render(const vector<Cube>& cubes,
    const map<BrickName, ColorName>& brick_name_to_color_name,
    uint_fast8_t color_value) const
{
    Sprites sprites{};
    for (const auto& cube : cubes)
        sprites.emplace_back(
            Rectangle{position_ + cube.position.scale(cube_size_), cube_size_},
            NvColor{brick_name_to_color_name.at(cube.brick_name), color_value});
    return sprites;
}

Sprites RenderCubes::render(const vector<vector<Cube>>& cubes,
    const map<BrickName, ColorName>& brick_name_to_color_name,
    uint_fast8_t color_value) const
{
    Sprites sprites{};
    for (const auto& row : cubes)
    {
        const Sprites rendered_sprites{
            render(row, brick_name_to_color_name, color_value)};
        sprites.insert(
            sprites.end(), rendered_sprites.begin(), rendered_sprites.end());
    }
    return sprites;
}

} // namespace Tetris::Ui
