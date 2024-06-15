#ifndef INCLUDE_UI_RENDER_PROGRESS_BAR_H
#define INCLUDE_UI_RENDER_PROGRESS_BAR_H

#include "ui/color/nv_color.h"
#include "ui/render/container/container.h"
#include "ui/render/rectangle.h"
#include "ui/render/sprite.h"
#include "vector_2/vector_2.h"

namespace Tetris::Ui
{

class RenderProgressBar final
{
public:
    constexpr RenderProgressBar(Rectangle container,
        RenderContainer render_container,
        NvColor on_color,
        NvColor off_color,
        Vector2 segment_size = {11, 2},
        int height = 10,
        int separator = 1)
      : container_{container},
        render_container_{render_container},
        on_color_{on_color},
        off_color_{off_color},
        segment_size_{segment_size},
        height_{height},
        separator_{separator}
    {}

    Sprites render(int value) const;

private:
    const Rectangle container_;
    const RenderContainer render_container_;
    const Vector2 segment_size_;
    const NvColor on_color_;
    const NvColor off_color_;
    const int height_;
    const int separator_;
};

} // namespace Tetris::Ui

#endif
