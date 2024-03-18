#ifndef INCLUDE_UI_COLOR_ID_NAME_H
#define INCLUDE_UI_COLOR_ID_NAME_H

#include <cassert>
#include <cstdint>
#include <map>

namespace Tetris::Ui
{

enum class ColorIdName: uint_fast8_t
{
    black,
    dark_candy_apple_red,
    islamic_green,
    windsor_tan,
    duke_blue,
    heliotrope_magenta,
    tiffany_blue,
    dark_gray,
    davy_s_grey,
    sunset_orange,
    screamin_green,
    dodie_yellow,
    very_light_blue,
    shocking_pink,
    electric_blue,
    white,
};

namespace
{
    const std::map<ColorIdName, uint_fast8_t> color_id_name_to_id
    {
        {ColorIdName::black, 0},
        {ColorIdName::dark_candy_apple_red, 1},
        {ColorIdName::islamic_green, 2},
        {ColorIdName::windsor_tan, 3},
        {ColorIdName::duke_blue, 4},
        {ColorIdName::heliotrope_magenta, 5},
        {ColorIdName::tiffany_blue, 6},
        {ColorIdName::dark_gray, 7},
        {ColorIdName::davy_s_grey, 8},
        {ColorIdName::sunset_orange, 9},
        {ColorIdName::screamin_green, 10},
        {ColorIdName::dodie_yellow, 11},
        {ColorIdName::very_light_blue, 12},
        {ColorIdName::shocking_pink, 13},
        {ColorIdName::electric_blue, 14},
        {ColorIdName::white, 15},
    };
}

inline uint_fast8_t get_color_id(ColorIdName name)
{
    assert(color_id_name_to_id.find(name) != color_id_name_to_id.end());
    return color_id_name_to_id.at(name);
}

}

#endif