#include "matrix_display_game_ui_impl.h"

#include <boost/range/irange.hpp>
#include <vector>

#include "brick.h"
#include "matrix_display.h"
#include "vector_2.h"

using boost::irange;
using std::vector;

namespace Tetris
{

MatrixDisplayGameUiImpl::MatrixDisplayGameUiImpl(MatrixDisplay& matrix)
:
    matrix{matrix},
    display_width{matrix.get_width()},
    display_height{matrix.get_height()}
{
    this->color_codes = this->create_color_codes();
    this->draw_background();
}

void MatrixDisplayGameUiImpl::draw_new_centered_brick(
    Vector2 display_position, int display_width, int display_height,
    const Brick& brick)
{
    this->draw_rectangle(display_position, display_width, display_height);
    const Vector2 centered_position{
        this->compute_brick_on_display_centered_position(
            display_position, display_width, display_height, brick)
    };
    this->draw_cubes(centered_position, brick.cubes);
}

//-------------------------------------------------------------------

MatrixDisplayGameUiImpl::ColorCodeMatrix
    MatrixDisplayGameUiImpl::create_color_codes() const
{
    ColorCodeMatrix color_codes{};
    color_codes.resize(display_height, vector<int>(display_width));
    return color_codes;
}

Vector2 MatrixDisplayGameUiImpl::compute_brick_center(const Brick& brick) const
{
    const Vector2 brick_position{
        Vector2{brick.get_min_x(), brick.get_min_y()}.abs() * cube_size
    };
    const Vector2 brick_center_position{
        Vector2{brick.get_width(), brick.get_height()} * cube_size / 2
    };
    return brick_position - brick_center_position;
}

Vector2 MatrixDisplayGameUiImpl::compute_brick_on_display_centered_position(
    Vector2 display_position,
    int display_width,
    int display_height,
    const Brick& brick) const
{
    const Vector2 display_center{
        this->compute_display_center(display_width, display_height)
    };
    const Vector2 brick_center{this->compute_brick_center(brick)};
    return display_position + display_center + brick_center;
}

void MatrixDisplayGameUiImpl::draw_rectangle(
    Vector2 position, int width, int height, int color_code)
{
    for (const auto& y : irange(height))
    {
        for (const auto& x : irange(width))
            this->draw_pixel(position + Vector2{x, y}, color_code);
    }
}

}