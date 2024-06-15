#ifndef UI_RENDER_CUBES_H
#define UI_RENDER_CUBES_H

#include <cstdint>
#include <functional>
#include <vector>

#include "brick/brick_name.h"
#include "cube/cube.h"
#include "ui/color/color_name.h"
#include "ui/render/rectangle.h"
#include "ui/render/sprite.h"
#include "vector2/vector2.h"

namespace Tetris::Ui
{

class RenderCubes final
{
public:
    RenderCubes(Vector2 position, int cube_size = 3, int outline_width = 1)
      : position_{position},
        cube_size_{cube_size},
        outline_{create_outline(outline_width)}
    {}

    Sprites render(const std::vector<Cube>& cubes,
        const std::map<BrickName, ColorName>& brick_name_to_color_name,
        uint_fast8_t color_value = 0xff,
        bool fill = true) const;

private:
    const Vector2 position_;
    const int cube_size_;
    const std::vector<Rectangle> outline_;

    std::vector<Rectangle> create_outline(int outline_width) const;

    Sprites render_filled(const std::vector<Cube>& cubes,
        const std::map<BrickName, ColorName>& brick_name_to_color_name,
        uint_fast8_t color_value) const;

    void for_each_outline_part(
        const std::function<void(const Vector2& position_offset,
            const Rectangle& outline_part)>& operation) const;

    Sprites render_outline(const std::vector<Cube>& cubes,
        const std::map<BrickName, ColorName>& brick_name_to_color_name,
        uint_fast8_t color_value) const;

    bool outline_part_should_be_added(const std::vector<Cube>& cubes,
        const Cube& cube,
        const Vector2& position_offset) const;

    bool outline_edge_should_be_added(const std::vector<Cube>& cubes,
        const Cube& cube,
        const Vector2& position_offset) const;

    std::vector<Cube> create_corner_neighbours(
        const Cube& cube, const Vector2& position_offset) const;

    bool outline_corner_should_be_added(const std::vector<Cube>& cubes,
        const Cube& cube,
        const Vector2& position_offset) const;

    Vector2 compute_cube_position(const Vector2& cube_position) const
    {
        return position_ + cube_position.scale(cube_size_);
    }
};

} // namespace Tetris::Ui

#endif
