#ifndef INCLUDE_PIXEL_H
#define INCLUDE_PIXEL_H

#include "color.h"
#include "vector_2.h"
#include <ostream>

struct Pixel final
{
    Vector2 coords;
    Color color;
    bool is_ghost;

    friend std::ostream& operator<<(std::ostream& os, const Pixel& pixel)
    {
        return os << "{" << pixel.coords.x << ", " << pixel.coords.y
            << ", " << pixel.color << "}";  
    }

    Pixel(int x, int y, Color color, bool is_ghost)
    :
        coords({x, y}),
        color(color),
        is_ghost(is_ghost)
    {}

    Pixel(int x, int y, Color color)
    :
        Pixel(x, y, color, false)
    {}

    Pixel(int x, int y)
    :
        Pixel(x, y, Color::black, false)
    {}

    bool operator==(const Pixel& other) const
    {
        return this->coords == other.coords
            and this->is_ghost == other.is_ghost
            and this->color == other.color;
    }

    bool empty() const
    {
        return this->color == Color::black;
    }

    void clear()
    {
        this->color = Color::black;
        this->is_ghost = false;
    }
};

#endif