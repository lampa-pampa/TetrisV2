#include "board/board_impl.h"
#include "brick/brick_generator_impl.h"
#include "config/filled_config.h"
#include "game_controller/console_game_controller_impl.h"
#include "game/game_impl.h"
#include "rng/rng_impl.h"
#include "score_counter/score_counter_impl.h"
#include "timer/timer_impl.h"
#include "ui/matrix_display/console/console_matrix_display_impl.h"
#include "ui/game_ui/matrix_display_game_ui_impl.h"

using Tetris::BoardImpl;
using Tetris::BrickGeneratorImpl;
using Tetris::config;
using Tetris::ConsoleGameControllerImpl;
using Tetris::GameImpl;
using Tetris::RngImpl;
using Tetris::ScoreCounterImpl;
using Tetris::TimerImpl;
using Tetris::Ui::ConsoleMatrixDisplayImpl;
using Tetris::Ui::MatrixDisplayGameUiImpl;

int main()
{
    ConsoleMatrixDisplayImpl matrix{
        {64, 64},
        {2, 1},
        0xff,
        {
            L' ',
            L'·',
            L'◦',
            L'◌',
            L'○',
            L'◎',
            L'◉',
            L'●',
        },
        {{
            {0, 16},
            {1, 1},
            {2, 2},
            {3, 3},
            {4, 4},
            {5, 5},
            {6, 6},
            {7, 7},
            {8, 8},
            {9, 9},
            {10, 10},
            {11, 11},
            {12, 12},
            {13, 13},
            {14, 14},
            {15, 15},
        }},
    };

    MatrixDisplayGameUiImpl ui{
        matrix,
        config.ui.controls,
        config.ui.components,
        config.ui.colors,
        config.ui.cube_size,
    };

    BoardImpl board{
        config.game.board.size,
        config.game.board.offset,
    };

    RngImpl rng{};

    BrickGeneratorImpl brick_generator{
        {config.game.bricks, rng},
        {config.game.color_ids, rng},
    };

    ScoreCounterImpl score_counter{
        config.game.score_counter.score_for,
    };

    GameImpl game{
        ui,
        board,
        brick_generator,
        score_counter,
        config.game.default_settings,
        config.game.brick_spawn_position,
        config.game.next_level_lines_quantity,
    };

    TimerImpl timer{
        config.game.default_settings.start_level,
    };

    ConsoleGameControllerImpl game_controller{
        timer,
        game,
        matrix.get_game_window(),
        config.controller.key_codes,
    };
  
    timer.connect_timeout([&game](){ game.handle_timeout(); });
    ui.connect_move_left_pressed([&game](){ game.handle_move_left(); });
    ui.connect_move_right_pressed([&game](){ game.handle_move_right(); });
    ui.connect_rotate_clockwise_pressed(
        [&game](){ game.handle_rotate_clockwise(); });
    ui.connect_rotate_counter_clockwise_pressed(
        [&game](){ game.handle_rotate_counter_clockwise(); });
    ui.connect_soft_drop_pressed([&game](){ game.handle_soft_drop(); });
    ui.connect_locking_hard_drop_pressed(
        [&game](){ game.handle_locking_hard_drop(); });
    ui.connect_no_locking_hard_drop_pressed(
        [&game](){ game.handle_no_locking_hard_drop(); });
    ui.connect_hold_pressed([&game](){ game.handle_hold(); });
    game.connect_reset_timeout([&timer](){ timer.reset_timeout(); });
    game.connect_set_timeout_delay(
        [&timer](int level){ timer.set_timeout_delay(level); });
    game_controller.connect_key_press(
        [&ui](int key_code){ ui.handle_key_press(key_code); });
    
    game_controller.run();

    return 0;
}