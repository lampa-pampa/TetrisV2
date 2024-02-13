#include "brick.h"
#include "pixel.h"
#include <algorithm>

using std::max_element;
using std::min_element;

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