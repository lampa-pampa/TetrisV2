#include "ui/game_ui/matrix_display_game_ui_impl.h"
#include "ui/render/sprite.h"

namespace Tetris::Ui
{

MatrixDisplayGameUiImpl::MatrixDisplayGameUiImpl(
    MatrixDisplay& matrix_display, const GameUiConfig& config)
  : matrix_display_{matrix_display},
    config_{config},
    key_code_to_signal_{
        {config.controls.left, move_left_pressed_},
        {config.controls.right, move_right_pressed_},
        {config.controls.rotate_clockwise, rotate_clockwise_pressed_},
        {config.controls.soft_drop, soft_drop_pressed_},
        {config.controls.locking_hard_drop, locking_hard_drop_pressed_},
        {config.controls.no_locking_hard_drop, no_locking_hard_drop_pressed_},
        {config.controls.rotate_counter_clockwise,
            rotate_counter_clockwise_pressed_},
        {config.controls.hold, hold_pressed_},
    },
    screen_{create_layer(matrix_display.get_size())},
    effects_layer_{},
    game_state_layer_{}
{}

void MatrixDisplayGameUiImpl::refresh_background()
{
    draw_sprite({{0, matrix_display_.get_size()},
        config_.graphic_engine.main.bg_color});
    for (const auto& rectangle : config_.graphic_engine.main.border)
        draw_sprite({rectangle, config_.graphic_engine.main.border_color});
    draw_sprites(config_.graphic_engine.score.label.display.render(
        config_.graphic_engine.score.label.text));
}

} // namespace Tetris::Ui
