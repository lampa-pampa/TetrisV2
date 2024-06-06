#ifndef INCLUDE_UI_SPRITE_H
#define INCLUDE_UI_SPRITE_H

#include <vector>

#include <boost/range/irange.hpp>

#include "ui/color/iv_color.h"
#include "ui/render/rectangle.h"
#include "vector_2/vector_2.h"

namespace Tetris::Ui
{

struct Sprite final
{
    Vector2 position;
    std::vector<Vector2> pixels;
    IvColor color;

    Sprite(const Vector2& position,
        const std::vector<Vector2>& pixels,
        const IvColor& color)
      : position{position},
        pixels{pixels},
        color{color}
    {}

    Sprite(const Rectangle& container, const IvColor& color)
      : position{container.position},
        pixels{},
        color{color}
    {
        for (const auto& y : boost::irange(container.size.y))
            for (const auto& x : boost::irange(container.size.x))
                pixels.emplace_back(x, y);
    }
};

using Sprites = std::vector<Sprite>;

} // namespace Tetris::Ui

#endif
