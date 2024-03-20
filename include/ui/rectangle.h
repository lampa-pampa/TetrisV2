#ifndef INCLUDE_UI_RECTANGLE_H
#define INCLUDE_UI_RECTANGLE_H

#include "vector_2.h"

namespace Tetris::Ui
{

struct Rectangle final
{
    Vector2 position;
    Vector2 size;

    constexpr Rectangle(Vector2 position, Vector2 size)
    :
        position{position},
        size{size}
    {}
};

}

#endif