#include "ui/matrix_display_game_ui_impl.h"

#include <cstdint>
#include <string>
#include <vector>

#include <boost/range/irange.hpp>

#include "brick.h"
#include "cube.h"
#include "ui/game_ui_colors.h"
#include "ui/game_ui_controls.h"
#include "ui/iv_color.h"
#include "ui/matrix_display.h"
#include "ui/rectangle.h"
#include "vector_2.h"

using boost::irange;
using std::vector;

namespace Tetris::Ui
{

MatrixDisplayGameUiImpl::MatrixDisplayGameUiImpl(
    MatrixDisplay& matrix,
    GameUiControls controls,
    GameUiComponents components,
    GameUiColors colors,
    int cube_size)
:
    matrix{matrix},
    key_code_to_signal{
        {controls.left, this->move_left_pressed},
        {controls.right, this->move_right_pressed},
        {controls.rotate_clockwise, this->rotate_clockwise_pressed},
        {controls.soft_drop, this->soft_drop_pressed},
        {controls.locking_hard_drop, this->locking_hard_drop_pressed},
        {controls.no_locking_hard_drop, this->no_locking_hard_drop_pressed},
        {controls.rotate_counter_clockwise,
            this->rotate_counter_clockwise_pressed},
        {controls.hold, this->hold_pressed},
    },
    components{components},
    colors{colors},
    cube_size{cube_size},
    main_layer{this->create_layer(matrix.get_size(), colors.iv.border)},
    cur_brick_cubes{}
{
    this->draw_background();
}

void MatrixDisplayGameUiImpl::handle_key_press(int key_code)
{
    if (const auto it{this->key_code_to_signal.find(key_code)};
        it != this->key_code_to_signal.end()
    )
        it->second();
}

void MatrixDisplayGameUiImpl::refresh_level_progress_bar(int quantity)
{
    const auto&[on_segments, off_segments]{
        this->components.progress_bar.level.create_segments(quantity)
    };
    this->draw_rectangles(
        on_segments,
        this->colors.iv.level.progress_bar.on);
    this->draw_rectangles(
        off_segments,
        this->colors.iv.level.progress_bar.off);
    this->draw_on_text_area(
        this->components.text.level,
        this->components.container.level_text,
        this->colors.iv.level.text);
}

void MatrixDisplayGameUiImpl::pause()
{
    this->draw_on_text_area(
        this->components.text.paused,
        this->components.text_area.game_state,
        this->colors.iv.game_state);
    this->flush_matrix();
}

void MatrixDisplayGameUiImpl::game_over()
{
    this->draw_on_text_area(
        this->components.text.game_over,
        this->components.text_area.game_state,
        this->colors.iv.game_state);
    this->flush_matrix();
}

//-------------------------------------------------------------------

MatrixDisplayGameUiImpl::IvColorMatrix
    MatrixDisplayGameUiImpl::create_layer(Vector2 size, IvColor color) const
{
    return IvColorMatrix(size.y, vector<IvColor>(size.x, color));
}

Vector2 MatrixDisplayGameUiImpl::compute_brick_center(
    Vector2 brick_size, bool align_to_left) const
{
    Vector2 brick_center_position{brick_size.scale(cube_size)};
    if (align_to_left)
        brick_center_position.x += 1;
    return brick_center_position.center();
}

Vector2 MatrixDisplayGameUiImpl::compute_brick_centered_position(
    const Brick& brick, bool align_to_left) const
{
    const Vector2 center_cube_position{
        Vector2{brick.get_min_x(), brick.get_min_y()}.abs().scale(cube_size)
    };
    const Vector2 brick_center_position{
        this->compute_brick_center(brick.get_size(), align_to_left)
    };
    return center_cube_position - brick_center_position;
}

void MatrixDisplayGameUiImpl::draw_background()
{
    this->draw_rectangles({
        this->components.container.next,
        this->components.container.hold,
        this->components.container.board,
        this->components.container.level_text,
        this->components.container.level_value,
        this->components.container.score_text,
        this->components.container.score_value,
        this->components.container.tetrises_text,
        this->components.container.tetrises_value,
    });
    this->draw_on_text_area(
        this->components.text.score,
        this->components.container.score_text,
        this->colors.iv.score.text);
    this->draw_on_text_area(
        this->components.text.tetrises,
        this->components.container.tetrises_text,
        this->colors.iv.tetrises.text);
}

void MatrixDisplayGameUiImpl::draw_cube(
    Vector2 position, const Cube& cube, uint_fast8_t color_value)
{
    const Vector2 position_in_px{(position + cube.position.scale(cube_size))};
    this->draw_rectangle(
        {position_in_px, cube_size}, {cube.color_id, color_value});
}

void MatrixDisplayGameUiImpl::draw_rectangle(const Rectangle& rectangle)
{
    this->draw_rectangle(rectangle,
        this->colors.iv.background);
}

void MatrixDisplayGameUiImpl::draw_rectangle(
    const Rectangle& rectangle, IvColor color)
{
    for (const auto& y : irange(rectangle.size.y))
    {
        for (const auto& x : irange(rectangle.size.x))
            this->draw_pixel(rectangle.position + Vector2{x, y}, color);
    }
}

void MatrixDisplayGameUiImpl::draw_text_line(
    const TextLine& line, IvColor color)
{
    this->draw_rectangle(line.background);
    Vector2 position{line.position};
    for (const auto& chr : line.chars)
    {
        this->draw_char(position, chr, color);
        position.x += chr.width + Char::separator;
    }
}

void MatrixDisplayGameUiImpl::draw_centered_brick_in_container(
    const Brick& brick,
    const Rectangle& rectangle,
    uint_fast8_t color_value,
    bool align_to_left)
{
    this->draw_rectangle(rectangle);
    const Vector2 cubes_position{
        rectangle.position + rectangle.size.center()
            + this->compute_brick_centered_position(brick, align_to_left)
    };
    this->draw_cubes(cubes_position, brick.cubes, color_value);
}

void MatrixDisplayGameUiImpl::refresh_next_brick(const Brick& brick)
{
    this->draw_centered_brick_in_container(
        brick,
        this->components.container.next,
        this->colors.value.brick.next,
        false);
}

void MatrixDisplayGameUiImpl::refresh_hold_brick(const Brick& brick)
{
    this->draw_centered_brick_in_container(
        brick,
        this->components.container.hold,
        this->colors.value.brick.hold,
        true);
}

void MatrixDisplayGameUiImpl::refresh_score(unsigned long long score)
{
    this->draw_on_text_area(
        score,
        this->components.text_area.score_value,
        this->colors.iv.score.value);
}

void MatrixDisplayGameUiImpl::refresh_tetrises(unsigned long long tetrises)
{
    this->draw_on_text_area(
        tetrises,
        this->components.text_area.tetrises_value,
        this->colors.iv.tetrises.value);
}

void MatrixDisplayGameUiImpl::refresh_level(int level)
{
    this->draw_on_text_area(
        level,
        this->components.text_area.level_value,
        this->colors.iv.level.value);
}

}