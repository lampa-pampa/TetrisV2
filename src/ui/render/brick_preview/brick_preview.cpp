#include "ui/render/brick_preview/brick_preview.h"
#include "ui/render/cubes/cubes.h"
#include "ui/render/sprite.h"
#include "vector_2/vector_2.h"

namespace Tetris::Ui
{

Sprites RenderBrickPreview::render(const Brick& brick) const
{
    Sprites sprites{render_container_.render(container_)};
    RenderCubes render_cubes{
        compute_brick_centered_position(brick), cube_size_};
    for (const auto& sprite : render_cubes.render(brick.cubes))
        sprites.emplace_back(std::move(sprite));
    return sprites;
}

Vector2 RenderBrickPreview::compute_brick_centered_position(
    const Brick& brick) const
{
    const Vector2 brick_center_offset{
        Vector2{brick.get_min_x(), brick.get_min_y()}.abs().scale(cube_size_)};
    Vector2 brick_size{brick.get_size().scale(cube_size_)};
    if (align_to_left_)
        brick_size.x += 1;
    return container_.position + container_.size.center() - brick_size.center()
        + brick_center_offset;
}

} // namespace Tetris::Ui
