#ifndef INCLUDE_UI_RECTANGLE_H
#define INCLUDE_UI_RECTANGLE_H

#include "ui/iv_color.h"
#include "vector_2.h"

namespace Tetris::Ui
{

struct Rectangle final
{
    Vector2 position;
    int width;
    int height;
    IvColor iv_color;

    constexpr Rectangle(
        Vector2 position, int width, int height, IvColor iv_color = {0, 0})
    :
        position{position},
        width{width},
        height{height},
        iv_color{iv_color}
    {}

    Vector2 get_center() const
    {
        return this->position + Vector2{this->width, this->height} / 2;
    }
};

}

#endif