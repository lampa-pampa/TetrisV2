#include "brick.h"
#include "pixel.h"
#include "vector_2.h"
#include <algorithm>
#include <ostream>
#include <boost/range/irange.hpp>

using std::swap;
using std::ostream;
using std::boolalpha;
using boost::irange;

Brick Brick::get_colored(const Brick& brick, Color color)
{
    Brick colored_brick{brick};
    for (auto& pixel : colored_brick.pixels)
        pixel.color = color;
    return colored_brick;
}

Brick Brick::get_translated(const Brick& brick, Vector2 position)
{
    Brick translated_brick{brick};
    for (auto& pixel : translated_brick.pixels)
        pixel.coords += position;
    return translated_brick;
}

Brick Brick::get_rotated(const Brick& brick, int quarters_rotation)
{
    Brick rotated_brick{brick};
    for (auto& pixel : rotated_brick.pixels)
    {
        for (const auto& i : irange<int>(quarters_rotation % 4))
        {
            swap(pixel.coords.x, pixel.coords.y);
            pixel.coords.x *= -1;
            if (rotated_brick.is_center_moved)
                ++pixel.coords.x;
        }
    }
    return rotated_brick;
}

Brick Brick::get_ghostified(const Brick& brick)
{
    Brick ghostified_brick{brick};
    for (auto& pixel : ghostified_brick.pixels)
        pixel.is_ghost = true;
    return ghostified_brick;
}

ostream& operator<<(ostream& os, const Brick& brick)
{
    os << "{{ ";
    for (auto it{brick.pixels.begin()}; it != brick.pixels.end(); ++it)
    {
        os << *it;
        if (it != brick.pixels.end() - 1)
            os << ", ";
    }
    return os << " }, " << boolalpha << brick.is_center_moved << "}";
}