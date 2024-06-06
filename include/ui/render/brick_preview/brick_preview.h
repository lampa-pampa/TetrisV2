#ifndef UI_RENDER_BRICK_PREVIEW_H
#define UI_RENDER_BRICK_PREVIEW_H

#include "brick/brick.h"
#include "ui/render/container/container.h"
#include "ui/render/rectangle.h"
#include "vector_2/vector_2.h"

namespace Tetris::Ui
{

class RenderBrickPreview final
{
public:
    RenderBrickPreview(Rectangle container,
        RenderContainer render_container,
        bool align_to_left = false,
        int cube_size = 3)
      : container_{container},
        render_container_{render_container},
        align_to_left_{align_to_left},
        cube_size_{cube_size}
    {}

    Sprites render(const Brick& brick) const;

private:
    const Rectangle container_;
    const RenderContainer render_container_;
    const bool align_to_left_;
    const int cube_size_;

    Vector2 compute_brick_centered_position(const Brick& brick) const;
};

} // namespace Tetris::Ui

#endif
