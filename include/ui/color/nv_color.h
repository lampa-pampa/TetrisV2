#ifndef INCLUDE_UI_NV_COLOR_H
#define INCLUDE_UI_NV_COLOR_H

#include <cstdint>
#include <iomanip>
#include <ostream>

#include "ui/color/color_name.h"
#include "utils/uint_fast8_t_ostream.h"

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

    bool operator==(const NvColor& other) const
    {
        return name == other.name and value == other.value;
    }

    friend std::ostream& operator<<(std::ostream& os, const NvColor& color)
    {
        return os << "{" << color.name << ", 0x" << std::hex << std::setw(2)
                  << std::setfill('0') << color.value << std::dec
                  << std::setfill(' ') << std::setw(0) << "}";
    }
};

} // namespace Tetris::Ui

#endif
