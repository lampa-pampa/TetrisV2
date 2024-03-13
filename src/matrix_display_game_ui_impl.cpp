#include "matrix_display_game_ui_impl.h"

#include <boost/range/irange.hpp>
#include <vector>

#include "brick.h"
#include "cube.h"
#include "matrix_display.h"
#include "vector_2.h"

using boost::irange;
using std::vector;

namespace Tetris
{

MatrixDisplayGameUiImpl::MatrixDisplayGameUiImpl(
    MatrixDisplay& matrix, int background_color_code)
:
    matrix{matrix},
    display_width{matrix.get_width()},
    display_height{matrix.get_height()},
    background_color_code{background_color_code}
{
    this->color_codes = this->create_color_codes();
    this->draw_background();
}

void MatrixDisplayGameUiImpl::handle_action_pressed(Action action)
{
    const auto it{this->action_to_signal.find(action)};
    assert(it != this->action_to_signal.end());
    it->second();
}

void MatrixDisplayGameUiImpl::draw_next_brick(const Brick& brick)
{
    this->next_brick_cubes = brick.cubes;
    this->draw_new_centered_brick(
        next_board_position, next_board_width, next_board_height, brick, false);
}

void MatrixDisplayGameUiImpl::draw_hold_brick(const Brick& brick)
{
    this->hold_brick_cubes = brick.cubes;
    this->draw_new_centered_brick(
        hold_board_position, next_board_width, next_board_height, brick, true);
}

//-------------------------------------------------------------------

MatrixDisplayGameUiImpl::ColorCodeMatrix
    MatrixDisplayGameUiImpl::create_color_codes() const
{
    ColorCodeMatrix color_codes{};
    color_codes.resize(display_height, vector<int>(display_width));
    return color_codes;
}

Vector2 MatrixDisplayGameUiImpl::compute_brick_center(
    int width, int height, bool align_to_left) const
{
    Vector2 brick_center_position{Vector2{width, height} * cube_size};
    if(align_to_left)
        brick_center_position.x += 1;
    return brick_center_position / 2;
}

Vector2 MatrixDisplayGameUiImpl::compute_brick_centered_position(
    const Brick& brick, bool align_to_left) const
{
    const Vector2 center_cube_position{
        Vector2{brick.get_min_x(), brick.get_min_y()}.abs() * cube_size
    };
    const Vector2 brick_center_position{
        this->compute_brick_center(
            brick.get_width(), brick.get_height(), align_to_left)
    };
    return center_cube_position - brick_center_position;
}

Vector2 MatrixDisplayGameUiImpl::compute_brick_on_display_centered_position(
    Vector2 display_position,
    int display_width,
    int display_height,
    const Brick& brick,
    bool align_to_left) const
{
    const Vector2 display_center{
        this->compute_display_center(display_width, display_height)
    };
    const Vector2 brick_center{
        this->compute_brick_centered_position(brick, align_to_left)};
    return display_position + display_center + brick_center;
}

void MatrixDisplayGameUiImpl::draw_background()
{
    this->draw_rectangle(
        {0, 0}, display_width, display_height,
        background_color_code);
}

void MatrixDisplayGameUiImpl::draw_cube(Vector2 position, const Cube& cube)
{
    const Vector2 position_in_px{position + cube.position * cube_size};
    this->draw_rectangle(
        position_in_px, cube_size, cube_size, cube.color_code);
}

void MatrixDisplayGameUiImpl::draw_new_centered_brick(
    Vector2 display_position,
    int display_width,
    int display_height,
    const Brick& brick,
    bool align_to_left)
{
    this->draw_rectangle(display_position, display_width, display_height);
    const Vector2 centered_position{
        this->compute_brick_on_display_centered_position(
            display_position,
            display_width,
            display_height,
            brick,
            align_to_left)
    };
    this->draw_cubes(centered_position, brick.cubes);
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