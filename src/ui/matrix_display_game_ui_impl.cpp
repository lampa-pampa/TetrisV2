#include "ui/matrix_display_game_ui_impl.h"

#include <map>
#include <vector>

#include <boost/range/irange.hpp>

#include "action.h"
#include "brick.h"
#include "cube.h"
#include "ui/matrix_display.h"
#include "ui/rectangle.h"
#include "vector_2.h"

using boost::irange;
using std::map;
using std::vector;

namespace Tetris::Ui
{

MatrixDisplayGameUiImpl::MatrixDisplayGameUiImpl(
    MatrixDisplay& matrix,
    std::map<int, Action> key_code_to_action,
    int background_color_code,
    int border_color_code,
    int font_color_code)
:
    matrix{matrix},
    key_code_to_action{key_code_to_action},
    display_width{matrix.get_width()},
    display_height{matrix.get_height()},
    background_color_code{background_color_code},
    border_color_code{border_color_code},
    font_color_code{font_color_code},
    cur_brick_cubes{}
{
    this->color_codes = this->create_color_codes();
    this->draw_background();
}

void MatrixDisplayGameUiImpl::handle_key_press(int key_code)
{
    if(const auto it{this->key_code_to_action.find(key_code)};
        it != this->key_code_to_action.end()
    )
        this->emit_action_signal(it->second);
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

void MatrixDisplayGameUiImpl::draw_background()
{
    this->draw_rectangle(
        {{0, 0}, display_width, display_height, border_color_code});
    for(const auto& rectangle : this->background_rectangles)
        draw_rectangle(rectangle);
    this->draw_on_text_area("LEVEL", level_text_area);
}

void MatrixDisplayGameUiImpl::draw_cube(Vector2 position, const Cube& cube)
{
    const Vector2 position_in_px{position + cube.position * cube_size};
    this->draw_rectangle(
        {position_in_px, cube_size, cube_size, cube.color_code});
}

void MatrixDisplayGameUiImpl::draw_rectangle(const Rectangle& rectangle)
{
    for (const auto& y : irange(rectangle.height))
    {
        for (const auto& x : irange(rectangle.width))
            this->draw_pixel(
                rectangle.position + Vector2{x, y}, rectangle.color_code);
    }
}

void MatrixDisplayGameUiImpl::emit_action_signal(Action action)
{
    const auto it{this->action_to_signal.find(action)};
    assert(it != this->action_to_signal.end());
    it->second();
}

}