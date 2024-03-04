#ifndef INCLUDE_COLOR_NAME_H
#define INCLUDE_COLOR_NAME_H

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

#endif