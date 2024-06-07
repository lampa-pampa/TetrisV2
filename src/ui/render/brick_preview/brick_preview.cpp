#include "ui/render/brick_preview/brick_preview.h"
#include "ui/render/cubes/cubes.h"
#include "ui/render/sprite.h"
#include "vector_2/vector_2.h"

namespace Tetris::Ui
{

Sprites RenderBrickPreview::render(const Brick& brick) const
{
    return render(brick, position_);
}

Sprites RenderBrickPreview::render(const std::deque<Brick>& bricks) const
{
    Sprites sprites{};
    Vector2 container_position{position_};
    for (const auto& brick : bricks)
    {
        const Sprites rendered_sprites{render(brick, container_position)};
        sprites.insert(
            sprites.end(), rendered_sprites.begin(), rendered_sprites.end());
        container_position.y += container_size_.y;
    }
    return sprites;
}

//-----------------------------------------------------------------------

Sprites RenderBrickPreview::render(
    const Brick& brick, const Vector2& container_position) const
{
    Sprites sprites{
        render_container_.render({container_position, container_size_})};
    RenderCubes render_cubes{
        compute_brick_centered_position(brick, container_position), cube_size_};
    const Sprites rendered_sprites{render_cubes.render(brick.cubes)};
    sprites.insert(
        sprites.end(), rendered_sprites.begin(), rendered_sprites.end());
    return sprites;
}

Vector2 RenderBrickPreview::compute_brick_centered_position(
    const Brick& brick, const Vector2& container_position) const
{
    const Vector2 brick_center_offset{
        Vector2{brick.get_min_x(), brick.get_min_y()}.abs().scale(cube_size_)};
    Vector2 brick_size{brick.get_size().scale(cube_size_)};
    if (align_to_left_)
        brick_size.x += 1;
    return container_position + container_size_.center() - brick_size.center()
        + brick_center_offset;
}

} // namespace Tetris::Ui
