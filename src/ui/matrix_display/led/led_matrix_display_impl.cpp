#include "ui/matrix_display/led/led_matrix_display_impl.h"

#include <cstdint>

#include <boost/range/irange.hpp>

#include "vector_2/vector_2.h"
#include "ui/color/iv_color.h"

using boost::irange;

namespace Tetris::Ui
{

LedMatrixDisplayImpl::LedMatrixDisplayImpl(
    Vector2 size,
    uint_fast8_t brightness,
    int chain_length,
    HUB75_I2S_CFG::i2s_pins pins,
    const std::map<uint_fast8_t, uint_fast8_t>& color_id_to_hs_color)
:
    size_{size},
    color_id_to_hs_color_{color_id_to_hs_color},
    matrix_{{
        static_cast<uint16_t>(size.x),
        static_cast<uint16_t>(size.y),
        static_cast<uint16_t>(chain_length),
        pins,
    }}
{
    matrix_.begin();
    matrix_.setBrightness8(brightness);
}

void LedMatrixDisplayImpl::refresh(const IvColorMatrix& colors)
{
    for (const auto& y : irange(size_.y))
    {
        for (const auto& x : irange(size_.x))
            refresh_pixel({x, y}, colors[y][x]);
    }
}

//-----------------------------------------------------------------------

void LedMatrixDisplayImpl::refresh_pixel(Vector2 position, IvColor color)
{
    uint16_t rgb_color;
    if(color.id == 0)
        rgb_color = matrix_.color565(0, 0, 0);
    else
        rgb_color = matrix_.color565(0, 0, 255);
    matrix_.drawPixel(position.x, position.y, rgb_color);
}

}