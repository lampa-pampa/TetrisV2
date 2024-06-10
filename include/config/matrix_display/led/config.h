#ifndef INCLUDE_CONSOLE_MATRIX_DISPLAY_CONFIG_H
#define INCLUDE_CONSOLE_MATRIX_DISPLAY_CONFIG_H

#include <cstdint>
#include <map>

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

#include "ui/color/color_name.h"
#include "ui/color/led/hs_color.h"
#include "vector_2/vector_2.h"

namespace Tetris::Ui
{

struct MatrixDisplayConfig final
{
    Vector2 size;
    uint_fast8_t brightness;
    int chain_length;
    HUB75_I2S_CFG::i2s_pins pins;
    std::map<ColorName, HsColor> color_name_to_hs_color;
    int max_color_value;
};

} // namespace Tetris::Ui

#endif
