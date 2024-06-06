#ifndef INCLUDE_UI_RENDER_CONTAINER_H
#define INCLUDE_UI_RENDER_CONTAINER_H

#include "ui/color/iv_color.h"
#include "ui/render/rectangle.h"
#include "ui/render/sprite.h"
#include "vector_2/vector_2.h"

namespace Tetris::Ui
{

class RenderContainer final
{
public:
    constexpr RenderContainer(IvColor bg_color,
        Vector2 padding,
        IvColor border_color,
        int border_width = 1)
      : padding_{padding},
        bg_color_{bg_color},
        border_color_{border_color},
        border_width_{border_width}
    {}

    constexpr RenderContainer(IvColor bg_color, Vector2 padding = {})
      : RenderContainer(bg_color, padding, {}, 0)
    {}

    Sprites render(const Rectangle& container) const;

private:
    const Vector2 padding_;
    const IvColor bg_color_;
    const IvColor border_color_;
    const int border_width_;

    std::vector<Rectangle> create_border(const Rectangle& background) const;
};

} // namespace Tetris::Ui

#endif
