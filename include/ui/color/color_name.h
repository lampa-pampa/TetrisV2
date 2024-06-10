#ifndef INCLUDE_UI_COLOR_NAME_H
#define INCLUDE_UI_COLOR_NAME_H

#include <cstdint>
#include <map>
#include <ostream>
#include <string>

namespace Tetris::Ui
{

enum class ColorName : uint_fast8_t
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

const std::map<ColorName, std::string> color_id_name_to_text{
    {ColorName::black, "black"},
    {ColorName::dark_candy_apple_red, "dark_candy_apple_red"},
    {ColorName::islamic_green, "islamic_green"},
    {ColorName::windsor_tan, "windsor_tan"},
    {ColorName::duke_blue, "duke_blue"},
    {ColorName::heliotrope_magenta, "heliotrope_magenta"},
    {ColorName::tiffany_blue, "tiffany_blue"},
    {ColorName::dark_gray, "dark_gray"},
    {ColorName::davy_s_grey, "davy_s_grey"},
    {ColorName::sunset_orange, "sunset_orange"},
    {ColorName::screamin_green, "screamin_green"},
    {ColorName::dodie_yellow, "dodie_yellow"},
    {ColorName::very_light_blue, "very_light_blue"},
    {ColorName::shocking_pink, "shocking_pink"},
    {ColorName::electric_blue, "electric_blue"},
    {ColorName::white, "white"},
};

inline std::ostream& operator<<(std::ostream& os, ColorName name)
{
    return os << "ColorName::" << color_id_name_to_text.at(name);
}

} // namespace Tetris::Ui

#endif
