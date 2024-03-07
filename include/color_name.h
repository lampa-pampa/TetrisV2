#ifndef INCLUDE_COLOR_NAME_H
#define INCLUDE_COLOR_NAME_H

#include <cassert>
#include <map>

namespace Tetris
{

enum class ColorName: int
{
    black,
    red,
    green,
    yellow,
    blue,
    purple,
    orange,
    pink,
    white,
};

namespace
{
    const std::map<ColorName, int> color_name_to_code
    {
        {ColorName::black, 0},
        {ColorName::red, 1},
        {ColorName::green, 2},
        {ColorName::blue, 3},
        {ColorName::yellow, 4},
        {ColorName::purple, 5},
        {ColorName::orange, 6},
        {ColorName::pink, 7},
        {ColorName::white, 8},
    };
}

inline int create_color(ColorName color_name)
{
    assert(color_name_to_code.find(color_name)
        != color_name_to_code.end());
    return color_name_to_code.at(color_name);
}

}

#endif