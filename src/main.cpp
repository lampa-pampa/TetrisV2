#include <ncurses.h>

#include "action.h"
#include "board_impl.h"
#include "brick_generator_impl.h"
#include "color_name.h"
#include "config.h"
#include "game_controller.h"
#include "game_impl.h"
#include "game_state.h"
#include "rng_impl.h"
#include "score_counter_impl.h"
#include "timer_impl.h"
#include "ui/console_matrix_display_impl.h"
#include "ui/matrix_display_game_ui_impl.h"
#include "ui/ncurses_colors.h"

using Tetris::Action;
using Tetris::BoardImpl;
using Tetris::BrickGeneratorImpl;
using Tetris::ColorName;
using Tetris::Config;
using Tetris::Ui::ConsoleMatrixDisplayImpl;
using Tetris::GameController;
using Tetris::GameImpl;
using Tetris::GameState;
using Tetris::get_color_code;
using Tetris::Ui::MatrixDisplayGameUiImpl;
using Tetris::Ui::NCursesColors;
using Tetris::RngImpl;
using Tetris::ScoreCounterImpl;
using Tetris::TimerImpl;

int main()
{
    Config config{
        {
            {10, 20, 2},
            {10, 1, 2},
            {
                {{ {-1, 0}, {0, 0}, {1, 0}, {2, 0} }, {1, 0} },
                {{ {0, -1}, {1, -1}, {0, 0}, {1, 0} }, {0, -1} },
                {{ {-1, -1}, {0, -1}, {0, 0}, {1, 0} }},
                {{ {0, -1}, {1, -1}, {-1, 0}, {0, 0} }},
                {{ {0, -1}, {-1, 0}, {0, 0}, {1, 0} }},
                {{ {-1, -1}, {-1, 0}, {0, 0}, {1, 0} }},
                {{ {1, -1}, {-1, 0}, {0, 0}, {1, 0} }},
            },
            {
                get_color_code(ColorName::red),
                get_color_code(ColorName::green),
                get_color_code(ColorName::blue),
                get_color_code(ColorName::yellow),
                get_color_code(ColorName::purple),
                get_color_code(ColorName::orange),
                get_color_code(ColorName::pink),
            },
            1,
            {true}
        },
        {
            {64, 64},
            {
                {KEY_DOWN, Action::soft_drop},
                {KEY_LEFT, Action::move_left},
                {KEY_RIGHT, Action::move_right},
                {KEY_UP, Action::rotate_clockwise},
                {'z', Action::rotate_counter_clockwise},
                {'x', Action::no_locking_hard_drop},
                {'c', Action::hold},
                {' ', Action::locking_hard_drop},
            },
            get_color_code(ColorName::black),
            get_color_code(ColorName::white),
            get_color_code(ColorName::red),
        },
        {
            'p',
            'q',
            -1,
        },
    };
    TimerImpl timer{};
    NCursesColors colors{};
    ConsoleMatrixDisplayImpl matrix{
        config.ui.display.width,
        config.ui.display.height,
        colors
    };
    MatrixDisplayGameUiImpl ui{
        matrix,
        config.ui.key_code_to_action,
        config.ui.background_color_code,
        config.ui.border_color_code,
        config.ui.font_color_code
    };
    BoardImpl board{
        config.game.board.width,
        config.game.board.height,
        config.game.board.offset
    };
    RngImpl rng{};
    BrickGeneratorImpl brick_generator{
        {config.game.bricks, rng},
        {config.game.color_codes, rng}
    };
    ScoreCounterImpl score_counter{
        config.game.score_counter.score_for_line,    
        config.game.score_counter.score_for_soft_drop,    
        config.game.score_counter.score_for_hard_drop,    
    };
    GameImpl game{
        ui,
        board,
        brick_generator,
        score_counter,
        config.game.brick_spawn_position_y,
        config.game.default_settings
    };
    GameController game_controller{timer, game};

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

    int key_code;
    ::WINDOW * game_window{matrix.get_game_window()};
    
    while ((key_code = ::wgetch(game_window)) != config.controls.quit_key_code)
    {
        const GameState state{game.get_state()};
        if(state == GameState::ended)
        {
            game.game_over();   
            continue;
        }
        
        if(key_code != config.controls.no_key_code)
        {
            if(key_code == config.controls.pause_key_code)
                game_controller.handle_pause_pressed();
            else if(state == GameState::in_progress)
                ui.handle_key_press(key_code);
        }
        
        if(timer.is_active())
        {
            if(state == GameState::ended)
                timer.stop();
            else
                timer.update_time();
        }
    }    
    return 0;
}