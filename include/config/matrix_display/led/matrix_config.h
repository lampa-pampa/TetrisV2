#ifndef INCLUDE_MATRIX_CONFIG_H
#define INCLUDE_MATRIX_CONFIG_H

#include <cstdint>
#include <map>

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

#include "vector_2/vector_2.h"

namespace Tetris
{

struct MatrixConfig final
{
    Vector2 size;
    uint_fast8_t brightness;
    int chain_length;
    HUB75_I2S_CFG::i2s_pins pins;
    const std::map<uint_fast8_t, uint_fast16_t>& color_id_to_hs_color;
};

}

#endif