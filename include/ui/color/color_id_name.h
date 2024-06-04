#ifndef INCLUDE_UI_COLOR_ID_NAME_H
#define INCLUDE_UI_COLOR_ID_NAME_H

#include <cstdint>
#include <map>
#include <ostream>
#include <string>

namespace Tetris::Ui
{

enum class ColorIdName : uint_fast8_t
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

const std::map<ColorIdName, std::string> color_id_name_to_text{
    {ColorIdName::black, "black"},
    {ColorIdName::dark_candy_apple_red, "dark_candy_apple_red"},
    {ColorIdName::islamic_green, "islamic_green"},
    {ColorIdName::windsor_tan, "windsor_tan"},
    {ColorIdName::duke_blue, "duke_blue"},
    {ColorIdName::heliotrope_magenta, "heliotrope_magenta"},
    {ColorIdName::tiffany_blue, "tiffany_blue"},
    {ColorIdName::dark_gray, "dark_gray"},
    {ColorIdName::davy_s_grey, "davy_s_grey"},
    {ColorIdName::sunset_orange, "sunset_orange"},
    {ColorIdName::screamin_green, "screamin_green"},
    {ColorIdName::dodie_yellow, "dodie_yellow"},
    {ColorIdName::very_light_blue, "very_light_blue"},
    {ColorIdName::shocking_pink, "shocking_pink"},
    {ColorIdName::electric_blue, "electric_blue"},
    {ColorIdName::white, "white"},
};

inline std::ostream& operator<<(std::ostream& os, ColorIdName name)
{
    return os << "ColorIdName::" << color_id_name_to_text.at(name);
}

} // namespace Tetris::Ui

#endif
