#ifndef INCLUDE_UI_HS_COLOR_H
#define INCLUDE_UI_HS_COLOR_H

#include <cstdint>

namespace Tetris::Ui
{

struct HsColor final
{
    uint_fast8_t hue;
    uint_fast8_t saturation;

    constexpr HsColor(uint_fast8_t hue, uint_fast8_t saturation)
    :
        hue{hue},
        saturation{saturation}
    {}
};

}

#endif