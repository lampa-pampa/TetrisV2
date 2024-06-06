#include "ui/render/cubes/cubes.h"

#include <vector>

#include "cube/cube.h"
#include "ui/color/iv_color.h"
#include "ui/render/rectangle.h"
#include "ui/render/sprite.h"
#include "vector_2/vector_2.h"

using std::vector;

namespace Tetris::Ui
{

Sprites RenderCubes::render(
    const vector<Cube>& cubes, uint_fast8_t color_value) const
{
    Sprites sprites{};
    for (const auto& cube : cubes)
        sprites.emplace_back(
            Rectangle{position_ + cube.position.scale(cube_size_), cube_size_},
            IvColor{cube.color_id_name, color_value});
    return sprites;
}

} // namespace Tetris::Ui
