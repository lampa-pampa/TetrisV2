#ifndef INCLUDE_UI_RGB_COLOR_H
#define INCLUDE_UI_RGB_COLOR_H

#include <cstdint>

#include "ui/color/led/hs_color.h"

namespace Tetris::Ui
{

struct RgbColor final
{
    uint_fast8_t red;
    uint_fast8_t green;
    uint_fast8_t blue;

    constexpr static RgbColor from_hsv(HsColor hs_color, uint_fast8_t value);

    constexpr RgbColor(uint_fast8_t red, uint_fast8_t green, uint_fast8_t blue)
    :
        red{red},
        green{green},
        blue{blue}
    {}
};

}

#endif