#ifndef INCLUDE_UI_RECTANGLE_H
#define INCLUDE_UI_RECTANGLE_H

#include "vector_2.h"

namespace Tetris
{

struct UiRectangle final
{
    Vector2 position;
    int width;
    int height;
    int color_code;

    constexpr UiRectangle(
        Vector2 position, int width, int height, int color_code)
    :
        position{position},
        width{width},
        height{height},
        color_code{color_code}
    {}

    constexpr UiRectangle(Vector2 position, int width, int height)
    :
        UiRectangle(position, width, height, 0)
    {}

    Vector2 get_center()
    {
        return this->position + Vector2{this->width, this->height} / 2;
    }
};

}

#endif