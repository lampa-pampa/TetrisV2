#include "ui/game_ui/matrix_display_game_ui_impl.h"

#include <cstdint>
#include <vector>

#include <boost/range/irange.hpp>

#include "brick/brick.h"
#include "cube/cube.h"
#include "ui/color/iv_color.h"
#include "ui/game_ui/game_ui_colors.h"
#include "ui/game_ui/game_ui_controls.h"
#include "ui/game_ui/game_ui_state_messages.h"
#include "ui/matrix_display/matrix_display.h"
#include "ui/rectangle/rectangle.h"
#include "vector_2/vector_2.h"

using boost::irange;
using std::vector;

namespace Tetris::Ui
{

MatrixDisplayGameUiImpl::MatrixDisplayGameUiImpl(MatrixDisplay& matrix,
    GameUiControls controls,
    GameUiComponents components,
    GameUiStateMessages state_messages,
    GameUiColors colors,
    int cube_size)
  : matrix_{matrix},
    key_code_to_signal_{
        {controls.left, move_left_pressed_},
        {controls.right, move_right_pressed_},
        {controls.rotate_clockwise, rotate_clockwise_pressed_},
        {controls.soft_drop, soft_drop_pressed_},
        {controls.locking_hard_drop, locking_hard_drop_pressed_},
        {controls.no_locking_hard_drop, no_locking_hard_drop_pressed_},
        {controls.rotate_counter_clockwise, rotate_counter_clockwise_pressed_},
        {controls.hold, hold_pressed_},
    },
    components_{components},
    state_messages_{state_messages},
    colors_{colors},
    cube_size_{cube_size},
    main_layer_{create_layer(matrix.get_size(), colors.iv.border)},
    cur_brick_cubes_{}
{
    draw_background();
}

void MatrixDisplayGameUiImpl::handle_key_press(int key_code)
{
    if (const auto it{key_code_to_signal_.find(key_code)};
        it != key_code_to_signal_.end())
        it->second();
}

void MatrixDisplayGameUiImpl::refresh_level_progress_bar(int quantity)
{
    const auto& [on_segments, off_segments]{
        components_.displays.level.bar.create_segments(quantity)};
    draw_rectangles(on_segments, colors_.iv.progress_bar.on);
    draw_rectangles(off_segments, colors_.iv.progress_bar.off);
    draw_text(components_.displays.level.display.label_text,
        colors_.iv.level.text,
        components_.displays.level.display.label_display);
}

void MatrixDisplayGameUiImpl::pause()
{
    draw_game_state(state_messages_.paused);
}

void MatrixDisplayGameUiImpl::game_over()
{
    draw_game_state(state_messages_.game_over);
}

//-------------------------------------------------------------------

MatrixDisplayGameUiImpl::IvColorMatrix MatrixDisplayGameUiImpl::create_layer(
    Vector2 size, IvColor color) const
{
    return IvColorMatrix(size.y, vector<IvColor>(size.x, color));
}

Vector2 MatrixDisplayGameUiImpl::compute_brick_center(
    Vector2 brick_size, bool align_to_left) const
{
    Vector2 brick_center_position{brick_size.scale(cube_size_)};
    if (align_to_left)
        brick_center_position.x += 1;
    return brick_center_position.center();
}

Vector2 MatrixDisplayGameUiImpl::compute_brick_centered_position(
    const Brick& brick, bool align_to_left) const
{
    const Vector2 center_cube_position{
        Vector2{brick.get_min_x(), brick.get_min_y()}.abs().scale(cube_size_)};
    const Vector2 brick_center_position{
        compute_brick_center(brick.get_size(), align_to_left)};
    return center_cube_position - brick_center_position;
}

void MatrixDisplayGameUiImpl::draw_background()
{
    draw_rectangles({
        components_.containers.next,
        components_.containers.hold,
        components_.containers.board,
        components_.containers.level_text,
        components_.containers.level_value,
        components_.containers.score_text,
        components_.containers.score_value,
        components_.containers.tetrises_text,
        components_.containers.tetrises_value,
    });
    draw_text(components_.displays.score.label_text,
        colors_.iv.score.text,
        components_.displays.score.label_display);
    draw_text(components_.displays.tetrises.label_text,
        colors_.iv.tetrises.text,
        components_.displays.tetrises.label_display);
}

void MatrixDisplayGameUiImpl::draw_cube(
    Vector2 position, const Cube& cube, uint_fast8_t color_value)
{
    const Vector2 cube_position{(position + cube.position.scale(cube_size_))};
    const IvColor iv_color{not cube.empty()
            ? IvColor{cube.color_id_name, color_value}
            : colors_.iv.background};
    draw_rectangle({cube_position, cube_size_}, iv_color);
}

void MatrixDisplayGameUiImpl::draw_rectangle(const Rectangle& rectangle)
{
    draw_rectangle(rectangle, colors_.iv.background);
}

void MatrixDisplayGameUiImpl::draw_rectangle(
    const Rectangle& rectangle, IvColor color)
{
    for (const auto& y : irange(rectangle.size.y))
    {
        for (const auto& x : irange(rectangle.size.x))
            draw_pixel(rectangle.position + Vector2{x, y}, color);
    }
}

void MatrixDisplayGameUiImpl::draw_centered_brick_in_container(
    const Brick& brick,
    const Rectangle& rectangle,
    uint_fast8_t color_value,
    bool align_to_left)
{
    draw_rectangle(rectangle);
    const Vector2 cubes_position{rectangle.position + rectangle.size.center()
        + compute_brick_centered_position(brick, align_to_left)};
    draw_cubes(cubes_position, brick.cubes, color_value);
}

void MatrixDisplayGameUiImpl::refresh_next_brick(const Brick& brick)
{
    draw_centered_brick_in_container(
        brick, components_.containers.next, colors_.value.brick.next, false);
}

void MatrixDisplayGameUiImpl::refresh_hold_brick(const Brick& brick)
{
    draw_centered_brick_in_container(
        brick, components_.containers.hold, colors_.value.brick.hold, true);
}

void MatrixDisplayGameUiImpl::refresh_score(unsigned long long score)
{
    draw_text(score,
        colors_.iv.score.value,
        components_.displays.score.value_display);
}

void MatrixDisplayGameUiImpl::refresh_tetrises(unsigned long long tetrises)
{
    draw_text(tetrises,
        colors_.iv.tetrises.value,
        components_.displays.tetrises.value_display);
}

void MatrixDisplayGameUiImpl::refresh_level(int level)
{
    draw_text(level,
        colors_.iv.level.value,
        components_.displays.level.display.value_display);
}

} // namespace Tetris::Ui
