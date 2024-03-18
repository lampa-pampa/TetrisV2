#ifndef INCLUDE_UI_RECTANGLE_H
#define INCLUDE_UI_RECTANGLE_H

#include "vector_2.h"

namespace Tetris::Ui
{

struct Rectangle final
{
    Vector2 position;
    int width;
    int height;
    int color_code;

    constexpr Rectangle(
        Vector2 position, int width, int height, int color_code)
    :
        position{position},
        width{width},
        height{height},
        color_code{color_code}
    {}

    constexpr Rectangle(Vector2 position, int width, int height)
    :
        Rectangle(position, width, height, 0)
    {}

    Vector2 get_center() const
    {
        return this->position + Vector2{this->width, this->height} / 2;
    }
};

}

#endif