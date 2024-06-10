#include "ui/render/brick_preview/brick_preview.h"

#include <map>

#include "brick/brick.h"
#include "brick/brick_name.h"
#include "ui/color/color_name.h"
#include "ui/render/cubes/cubes.h"
#include "ui/render/sprite.h"
#include "vector_2/vector_2.h"

using std::map;

namespace Tetris::Ui
{

Sprites RenderBrickPreview::render(const std::deque<Brick>& bricks,
    const std::map<BrickName, ColorName>& brick_name_to_color_name) const
{
    Sprites sprites{render_container_.render(container_)};
    Vector2 container_position{container_.position};
    for (const auto& brick : bricks)
    {
        const Sprites rendered_sprites{
            render(brick, brick_name_to_color_name, container_position)};
        sprites.insert(
            sprites.end(), rendered_sprites.begin(), rendered_sprites.end());
        container_position.y += brick_container_size_.y;
    }
    return sprites;
}

Sprites RenderBrickPreview::render(const Brick& brick,
    const std::map<BrickName, ColorName>& brick_name_to_color_name) const
{
    Sprites sprites{render_container_.render(container_)};
    const Sprites rendered_sprites{
        render(brick, brick_name_to_color_name, container_.position)};
    sprites.insert(
        sprites.end(), rendered_sprites.begin(), rendered_sprites.end());
    return sprites;
}

//-----------------------------------------------------------------------

Vector2 RenderBrickPreview::compute_brick_centered_position(
    const Brick& brick, const Vector2& container_position) const
{
    const Vector2 brick_center_offset{
        Vector2{brick.get_min_x(), brick.get_min_y()}.abs().scale(cube_size_)};
    Vector2 brick_size{brick.get_size().scale(cube_size_)};
    if (align_to_left_)
        brick_size.x += 1;
    return container_position + brick_container_size_.center()
        - brick_size.center() + brick_center_offset;
}

Sprites RenderBrickPreview::render(const Brick& brick,
    const map<BrickName, ColorName>& brick_name_to_color_name,
    const Vector2& container_position) const
{
    RenderCubes render_cubes{
        compute_brick_centered_position(brick, container_position), cube_size_};
    return render_cubes.render(brick.get_cubes(), brick_name_to_color_name);
}

} // namespace Tetris::Ui
