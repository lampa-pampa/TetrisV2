#include <chrono>
#include <memory>
#include <thread>

#include "board/board_impl.h"
#include "brick/brick_generator_impl.h"
#include "config/filled_config.h"
#include "game_controller/game_controller.h"
#include "game/game_impl.h"
#include "rng/rng_impl.h"
#include "score_counter/score_counter_impl.h"
#include "timer/timer_impl.h"
#include "ui/game_ui/matrix_display_game_ui_impl.h"
#include "ui/matrix_display/create_matrix_display_impl.h"
#include "ui/matrix_display/matrix_display.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::shared_ptr;
using std::this_thread::sleep_for;
using Tetris::BoardImpl;
using Tetris::BrickGeneratorImpl;
using Tetris::config;
using Tetris::GameController;
using Tetris::GameImpl;
using Tetris::RngImpl;
using Tetris::ScoreCounterImpl;
using Tetris::TimerImpl;
using Tetris::Ui::create_matrix_display_impl;
using Tetris::Ui::MatrixDisplay;
using Tetris::Ui::MatrixDisplayGameUiImpl;

int main()
{
    shared_ptr<MatrixDisplay> matrix{
        create_matrix_display_impl(config.ui.matrix)
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

    GameController game_controller{
        timer,
        game,
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
    game_controller.connect_get_pressed_key_code(
        [&matrix](){ return matrix->get_pressed_key_code(); });
    game_controller.connect_key_press(
        [&ui](int key_code){ ui.handle_key_press(key_code); });
    
    auto previous_time{system_clock::now()};

    while(true)
    {
        const auto now{system_clock::now()};
        const auto delta_time{duration_cast<milliseconds>(now - previous_time)};
        if(not game_controller.update(delta_time.count()))
            break;
        previous_time = now;
        sleep_for(milliseconds(5));
    }

    return 0;
}