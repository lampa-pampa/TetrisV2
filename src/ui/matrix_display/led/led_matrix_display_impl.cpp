#include "ui/matrix_display/led/led_matrix_display_impl.h"

#include <cstdint>

#include <boost/range/irange.hpp>

#include "config/matrix_display/led/config.h"
#include "ui/color/iv_color.h"
#include "ui/color/led/rgb_color.h"
#include "vector_2/vector_2.h"

using boost::irange;

namespace Tetris::Ui
{

LedMatrixDisplayImpl::LedMatrixDisplayImpl(const MatrixDisplayConfig& config)
  : size_{config.size},
    rgb_colors_{config.color_id_to_hs_color, config.max_color_value},
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
    const RgbColor rgb_color{rgb_colors_.get(color)};
    const uint_fast16_t color565{
        matrix_.color565(rgb_color.red, rgb_color.green, rgb_color.blue)};
    matrix_.drawPixel(position.x, position.y, color565);
}

} // namespace Tetris::Ui
