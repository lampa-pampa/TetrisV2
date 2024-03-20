#ifndef INCLUDE_UI_COLOR_ID_NAME_H
#define INCLUDE_UI_COLOR_ID_NAME_H

#include <cstdint>

namespace Tetris::Ui
{

enum class ColorIdName: uint_fast8_t
{
    black = 0,
    dark_candy_apple_red = 1,
    islamic_green = 2,
    windsor_tan = 3,
    duke_blue = 4,
    heliotrope_magenta = 5,
    tiffany_blue = 6,
    dark_gray = 7,
    davy_s_grey = 8,
    sunset_orange = 9,
    screamin_green = 10,
    dodie_yellow = 11,
    very_light_blue = 12,
    shocking_pink = 13,
    electric_blue = 14,
    white = 15,
};

constexpr uint_fast8_t get_color_id(ColorIdName name)
{
    return static_cast<uint_fast8_t>(name);
}

}

#endif