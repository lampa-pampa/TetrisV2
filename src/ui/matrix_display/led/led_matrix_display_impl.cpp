#include "ui/matrix_display/led/led_matrix_display_impl.h"

#include <cstdint>

#include <boost/range/irange.hpp>

#include "ui/color/iv_color.h"
#include "ui/matrix_display/led/config/matrix_config.h"
#include "vector_2/vector_2.h"

using boost::irange;

namespace Tetris::Ui
{

LedMatrixDisplayImpl::LedMatrixDisplayImpl(const MatrixConfig& config)
:
    size_{config.size},
    color_id_to_hs_color_{config.color_id_to_hs_color},
    matrix_{{
        static_cast<uint16_t>(config.size.x),
        static_cast<uint16_t>(config.size.y),
        static_cast<uint16_t>(config.chain_length),
        config.pins,
    }}
{
    matrix_.begin();
    matrix_.setBrightness8(config.brightness);
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