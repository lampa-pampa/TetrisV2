#ifndef INCLUDE_UI_NV_COLOR_H
#define INCLUDE_UI_NV_COLOR_H

#include <cstdint>

#include "ui/color/color_name.h"

namespace Tetris::Ui
{

struct NvColor final
{
    ColorName name;
    uint_fast8_t value;

    constexpr NvColor(
        ColorName name = ColorName::black, uint_fast8_t value = 0xff)
      : name{name},
        value((name == ColorName::black) ? 0 : value)
    {}
};

} // namespace Tetris::Ui

#endif
