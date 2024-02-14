#include "brick.h"
#include "pixel.h"
#include "vector_2.h"
#include <algorithm>
#include <utility>
#include <vector>

using std::swap;
using std::max_element;
using std::min_element;
using std::vector;

Brick Brick::get_colored(const Brick &brick, Color color)
{
    Brick colored_brick{brick};
    for(Pixel &pixel : colored_brick.pixels)
        pixel.color = color;
    return colored_brick;
}

Brick Brick::get_translated(const Brick &brick, Vector2 position)
{
    Brick translated_brick{brick};
    for(Pixel &pixel : translated_brick.pixels)
        pixel.coords += position;
    return translated_brick;
}

Brick Brick::get_rotated(const Brick &brick, int quarters_rotation)
{
    Brick rotated_brick{brick};
    for(Pixel &pixel : rotated_brick.pixels)
    {
        for(int i{0}; i < quarters_rotation % 4; ++i)
        {
            swap(pixel.coords.x, pixel.coords.y);
            pixel.coords.x *= -1;
            if(rotated_brick.is_center_moved)
                ++pixel.coords.x;
        }
    }
    return rotated_brick;
}

Brick Brick::get_transformed(const Brick &brick, int quarters_rotation, Vector2 position)
{
    const Brick rotated_brick{get_rotated(brick, quarters_rotation)};
    return get_translated(rotated_brick, position);
}

Brick Brick::get_ghostified(const Brick &brick)
{
    Brick ghostified_brick{brick};
    for(Pixel &pixel : ghostified_brick.pixels)
        pixel.is_ghost = true;
    return ghostified_brick;
}

Brick::Brick(vector<Pixel> pixels, bool is_center_moved)
:
    pixels(pixels),
    is_center_moved(is_center_moved)
{}
    
    
Brick::Brick(std::vector<Pixel> pixels)
:
    Brick(pixels, false)
{}

int Brick::get_min_x() const
{
    return min_element(this->pixels.begin(), this->pixels.end(), [](const Pixel &a, const Pixel &b)-> bool{
        return a.coords.x < b.coords.x;
    })->coords.x;
}

int Brick::get_max_x() const
{
    return max_element(this->pixels.begin(), this->pixels.end(), [](const Pixel &a, const Pixel &b)-> bool{
        return a.coords.x < b.coords.x;
    })->coords.x;
}

int Brick::get_min_y() const
{
    return min_element(this->pixels.begin(), this->pixels.end(), [](const Pixel &a, const Pixel &b)-> bool{
        return a.coords.y < b.coords.y;
    })->coords.y;
}

int Brick::get_max_y() const
{
    return max_element(this->pixels.begin(), this->pixels.end(), [](const Pixel &a, const Pixel &b)-> bool{
        return a.coords.y < b.coords.y;
    })->coords.y;
}

bool Brick::operator==(const Brick &other) const
{
    return this->pixels == other.pixels
        and this->is_center_moved == other.is_center_moved;
}