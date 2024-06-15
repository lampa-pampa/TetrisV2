#include "ui/render/progress_bar/progress_bar.h"

#include <boost/range/irange.hpp>

#include "ui/render/rectangle.h"
#include "ui/render/sprite.h"
#include "vector_2/vector_2.h"

using boost::irange;

namespace Tetris::Ui
{

Sprites RenderProgressBar::render(int value) const
{
    Vector2 segment_position{container_.position};
    Sprites sprites{render_container_.render(container_)};
    for (const auto& i : irange(height_))
    {
        const Rectangle segment{segment_position, segment_size_};
        if (height_ - i <= value)
            sprites.emplace_back(std::move(segment), on_color_);
        else
            sprites.emplace_back(std::move(segment), off_color_);
        segment_position.y += segment_size_.y + separator_;
    }
    return sprites;
}

} // namespace Tetris::Ui
