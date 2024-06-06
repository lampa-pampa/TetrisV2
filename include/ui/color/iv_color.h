#ifndef INCLUDE_UI_IV_COLOR_H
#define INCLUDE_UI_IV_COLOR_H

#include <cstdint>

#include "ui/color/color_id_name.h"

namespace Tetris::Ui
{

struct IvColor final
{
    uint_fast8_t id;
    uint_fast8_t value;

    constexpr IvColor(uint_fast8_t id, uint_fast8_t value): id{id}, value{value}
    {}

    constexpr IvColor(ColorIdName id_name, uint_fast8_t value = 0xff)
      : IvColor(static_cast<uint_fast8_t>(id_name),
            (id_name == ColorIdName::black) ? 0 : value)
    {}

    constexpr IvColor(): IvColor(ColorIdName::black) {}
};

} // namespace Tetris::Ui

#endif
