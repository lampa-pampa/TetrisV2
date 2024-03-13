#include <map>
#include <ncurses.h>

#include "action.h"
#include "board_impl.h"
#include "brick_generator_impl.h"
#include "color_name.h"
#include "config.h"
#include "console_matrix_display_impl.h"
#include "game_controller.h"
#include "game_impl.h"
#include "matrix_display_game_ui_impl.h"
#include "ncurses_colors.h"
#include "rng_impl.h"
#include "score_counter_impl.h"
#include "timer_mock.h"

using std::map;
using Tetris::Action;
using Tetris::BoardImpl;
using Tetris::BrickGeneratorImpl;
using Tetris::ColorName;
using Tetris::Config;
using Tetris::ConsoleMatrixDisplayImpl;
using Tetris::get_color_code;
using Tetris::GameController;
using Tetris::GameImpl;
using Tetris::MatrixDisplayGameUiImpl;
using Tetris::NCursesColors;
using Tetris::RngImpl;
using Tetris::ScoreCounterImpl;
using Tetris::TimerMock;

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
            get_color_code(ColorName::white),
        },
    };
    TimerMock timer{};
    NCursesColors colors{};
    ConsoleMatrixDisplayImpl matrix{
        config.ui.display.width,
        config.ui.display.height,
        colors
    };
    MatrixDisplayGameUiImpl ui{
        matrix,
        config.ui.background_color_code
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
    constexpr int quit_key_code{'q'};
    constexpr int no_key_press_code{-1};
    const map<int, Action> input_key_code_to_action{
        {KEY_DOWN, Action::soft_drop},
        {KEY_LEFT, Action::move_left},
        {KEY_RIGHT, Action::move_right},
        {KEY_UP, Action::rotate_clockwise},
        {'z', Action::rotate_counter_clockwise},
        {'x', Action::no_locking_hard_drop},
        {'c', Action::hold},
        {' ', Action::locking_hard_drop},
        {'p', Action::pause},
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
    ui.connect_pause_pressed([&game_controller](){
        game_controller.handle_pause_pressed();});

    int input_key_code;
    ::WINDOW * game_window{matrix.get_game_window()};
    
    while ((input_key_code = ::wgetch(game_window)) != quit_key_code)
    {
        if(input_key_code == no_key_press_code)
            continue;
        const auto it{input_key_code_to_action.find(input_key_code)}; 
        if(it != input_key_code_to_action.end())
            ui.handle_action_pressed(it->second);
    }    
    return 0;
}