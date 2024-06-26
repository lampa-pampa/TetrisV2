#ifndef INCLUDE_UI_SPRITE_H
#define INCLUDE_UI_SPRITE_H

#include <ostream>
#include <vector>

#include <boost/range/irange.hpp>

#include "ui/color/nv_color.h"
#include "ui/render/rectangle.h"
#include "vector2/vector2.h"

namespace Tetris::Ui
{

struct Sprite final
{
    Vector2 position;
    std::vector<Vector2> pixels;
    NvColor color;

    friend std::ostream& operator<<(std::ostream& os, const Sprite& sprite)
    {
        return os << "{" << sprite.position << ", " << sprite.pixels << ", "
                  << sprite.color << "}";
    }

    Sprite(const Vector2& position,
        const std::vector<Vector2>& pixels,
        const NvColor& color)
      : position{position},
        pixels{pixels},
        color{color}
    {}

    Sprite(const Rectangle& container, const NvColor& color)
      : position{container.position},
        pixels{},
        color{color}
    {
        for (const auto& y : boost::irange(container.size.y))
            for (const auto& x : boost::irange(container.size.x))
                pixels.emplace_back(x, y);
    }

    bool operator==(const Sprite& other) const
    {
        return position == other.position and pixels == other.pixels
            and color == other.color;
    }
};

using Sprites = std::vector<Sprite>;

} // namespace Tetris::Ui

#endif
