#ifndef INCLUDE_UI_RECTANGLE_H
#define INCLUDE_UI_RECTANGLE_H

#include "vector2/vector2.h"

namespace Tetris::Ui
{

struct Rectangle final
{
    Vector2 position;
    Vector2 size;

    constexpr Rectangle(const Vector2& position, const Vector2& size)
      : position{position},
        size{size}
    {}
};

} // namespace Tetris::Ui

#endif
