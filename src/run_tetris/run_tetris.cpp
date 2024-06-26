#include "run_tetris/run_tetris.h"

#include "board/board_impl.h"
#include "config/config.h"
#include "game/bricks.h"
#include "game/game_impl.h"
#include "game_controller/game_controller.h"
#include "rng/rng.h"
#include "run_tetris/main_loop.h"
#include "score_counter/score_counter_impl.h"
#include "timer/timer_impl.h"
#include "ui/game_ui/matrix_display_game_ui_impl.h"
#include "ui/keyboard/keyboard.h"
#include "ui/matrix_display/matrix_display.h"

namespace Tetris
{

void run_tetris(const Config& config,
    Ui::Keyboard& keyboard,
    Ui::MatrixDisplay& matrix_display,
    Rng& rng)
{
    Ui::MatrixDisplayGameUiImpl ui{
        matrix_display,
        config.ui,
    };

    BoardImpl board{
        config.game.board.size,
    };

    ScoreCounterImpl score_counter{
        config.game.score_counter.score_for,
    };

    GameBricks bricks{
        {
            config.game.bricks,
            rng,
        },
        config.game.brick_spawn_position,
    };

    GameImpl game{
        ui,
        board,
        score_counter,
        bricks,
        config.game.default_settings,
    };

    TimerImpl timer{
        config.game.default_settings.start_level,
    };

    GameController game_controller{
        game,
        timer,
        keyboard,
        config.controller.key_codes,
    };

    timer.connect_timeout([&game]() { game.handle_timeout(); });
    ui.connect_move_left_pressed([&game]() { game.handle_move_left(); });
    ui.connect_move_right_pressed([&game]() { game.handle_move_right(); });
    ui.connect_rotate_clockwise_pressed(
        [&game]() { game.handle_rotate_clockwise(); });
    ui.connect_rotate_counter_clockwise_pressed(
        [&game]() { game.handle_rotate_counter_clockwise(); });
    ui.connect_soft_drop_pressed([&game]() { game.handle_soft_drop(); });
    ui.connect_locking_hard_drop_pressed(
        [&game]() { game.handle_locking_hard_drop(); });
    ui.connect_no_locking_hard_drop_pressed(
        [&game]() { game.handle_no_locking_hard_drop(); });
    ui.connect_hold_pressed([&game]() { game.handle_hold(); });
    game.connect_reset_timeout([&timer]() { timer.reset_timeout(); });
    game.connect_set_timeout_delay(
        [&timer](int level) { timer.set_timeout_delay(level); });
    game_controller.connect_key_press(
        [&ui](int key_code) { ui.handle_key_press(key_code); });

    main_loop(game_controller);
}

} // namespace Tetris
