#ifndef INCLUDE_UI_RENDER_CONTAINER_H
#define INCLUDE_UI_RENDER_CONTAINER_H

#include "ui/color/nv_color.h"
#include "ui/render/rectangle.h"
#include "ui/render/sprite.h"
#include "vector2/vector2.h"

namespace Tetris::Ui
{

class RenderContainer final
{
public:
    constexpr RenderContainer(NvColor bg_color,
        Vector2 padding,
        NvColor border_color,
        int border_width = 1)
      : padding_{padding},
        bg_color_{bg_color},
        border_color_{border_color},
        border_width_{border_width}
    {}

    constexpr RenderContainer(NvColor bg_color, Vector2 padding = {})
      : RenderContainer(bg_color, padding, {}, 0)
    {}

    Sprites render(const Rectangle& container) const;

private:
    const Vector2 padding_;
    const NvColor bg_color_;
    const NvColor border_color_;
    const int border_width_;

    std::vector<Rectangle> create_border(const Rectangle& background) const;
};

} // namespace Tetris::Ui

#endif
