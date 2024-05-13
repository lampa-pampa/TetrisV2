#ifndef INCLUDE_UI_IV_COLOR_H
#define INCLUDE_UI_IV_COLOR_H

#include <cstdint>

namespace Tetris::Ui
{

struct IvColor final
{
    uint_fast8_t id;
    uint_fast8_t value;

    constexpr IvColor(uint_fast8_t id, uint_fast8_t value)
    :
        id{id},
        value{value}
    {}
};

}

#endif