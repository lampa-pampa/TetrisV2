#ifndef INCLUDE_PIXEL_H
#define INCLUDE_PIXEL_H

#include <ostream>

#include "vector_2.h"

namespace Tetris
{

struct Pixel final
{
    Vector2 coords;
    int color_code;
    bool is_ghost;

    friend std::ostream& operator<<(std::ostream& os, const Pixel& pixel)
    {
        return os << "{" << pixel.coords.x << ", " << pixel.coords.y
            << ", " << pixel.color_code << "}";  
    }

    Pixel(int x, int y, int color_code, bool is_ghost)
    :
        coords{x, y},
        color_code{color_code},
        is_ghost{is_ghost}
    {}

    Pixel(int x, int y, int color_code)
    :
        Pixel{x, y, color_code, false}
    {}

    Pixel(int x, int y)
    :
        Pixel{x, y, 0, false}
    {}

    bool operator==(const Pixel& other) const
    {
        return this->coords == other.coords
            and this->is_ghost == other.is_ghost
            and this->color_code == other.color_code;
    }

    bool empty() const
    {
        return this->color_code == 0;
    }

    void clear()
    {
        this->color_code = 0;
        this->is_ghost = false;
    }
};

}

#endif