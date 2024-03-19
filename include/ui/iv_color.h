#ifndef INCLUDE_UI_IV_COLOR_H
#define INCLUDE_UI_IV_COLOR_H

#include <cstdint>

namespace Tetris::Ui
{

struct IvColor
{
    uint_fast8_t id;
    uint_fast8_t value;

    constexpr IvColor()
    :
        id{0},
        value{0}
    {}

    constexpr IvColor(uint_fast8_t id, uint_fast8_t value = 0xff)
    :
        id{id},
        value{value}
    {}
};

}

#endif