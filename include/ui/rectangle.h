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

    constexpr Rectangle(Vector2 position, int width, int height)
    :
        position{position},
        width{width},
        height{height}
    {}

    Vector2 get_center() const
    {
        return this->position + Vector2{this->width, this->height}.center();
    }
};

struct Rectangle2 final
{
    Vector2 position;
    int width;
    int height;

    constexpr Rectangle2(Vector2 position, int width, int height, int, int)
    :
        position{position},
        width{width},
        height{height}
    {}

    Vector2 get_center() const
    {
        return this->position + Vector2{this->width, this->height}.center();
    }
};

}

#endif