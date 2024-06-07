#include "ui/render/container/container.h"

#include <vector>

#include "ui/render/rectangle.h"
#include "ui/render/sprite.h"

using std::vector;

namespace Tetris::Ui
{

Sprites RenderContainer::render(const Rectangle& container) const
{
    const Rectangle background{
        container.position - padding_, container.size + padding_.scale(2)};
    Sprites sprites{{background, bg_color_}};
    if (border_width_ > 0)
    {
        for (const auto& rectangle : create_border(background))
            sprites.emplace_back(rectangle, border_color_);
    }
    return sprites;
}

//-----------------------------------------------------------------------

vector<Rectangle> RenderContainer::create_border(const Rectangle& bg) const
{
    return {
        {bg.position - border_width_,
            {bg.size.x + border_width_ * 2, border_width_}},
        {{bg.position.x - border_width_, bg.position.y},
            {border_width_, bg.size.y}},
        {{bg.position.x + bg.size.x, bg.position.y},
            {border_width_, bg.size.y}},
        {{bg.position.x - border_width_, bg.position.y + bg.size.y},
            {bg.size.x + border_width_ * 2, border_width_}},
    };
}

} // namespace Tetris::Ui
