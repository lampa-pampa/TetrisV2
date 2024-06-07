#ifndef UI_RENDER_BRICK_PREVIEW_H
#define UI_RENDER_BRICK_PREVIEW_H

#include <deque>

#include "brick/brick.h"
#include "ui/render/container/container.h"
#include "vector_2/vector_2.h"

namespace Tetris::Ui
{

class RenderBrickPreview final
{
public:
    RenderBrickPreview(Vector2 position,
        Vector2 container_size,
        RenderContainer render_container,
        bool align_to_left = false,
        int cube_size = 3)
      : position_{position},
        container_size_{container_size},
        render_container_{render_container},
        align_to_left_{align_to_left},
        cube_size_{cube_size}
    {}

    Sprites render(const std::deque<Brick>& bricks) const;
    Sprites render(const Brick& brick) const;

private:
    const Vector2 position_;
    const Vector2 container_size_;
    const RenderContainer render_container_;
    const bool align_to_left_;
    const int cube_size_;

    Sprites render(const Brick& brick, const Vector2& container_position) const;
    Vector2 compute_brick_centered_position(
        const Brick& brick, const Vector2& container_position) const;
};

} // namespace Tetris::Ui

#endif
