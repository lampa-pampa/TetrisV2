#include <ncurses.h>

#include "board_impl.h"
#include "brick_generator_impl.h"
#include "color_name.h"
#include "config.h"
#include "console_matrix_display_impl.h"
#include "game_controller.h"
#include "game_impl.h"
#include "game_state.h"
#include "matrix_display_game_ui_impl.h"
#include "ncurses_colors.h"
#include "rng_impl.h"
#include "score_counter_impl.h"
#include "timer_mock.h"

using Tetris::BoardImpl;
using Tetris::BrickGeneratorImpl;
using Tetris::ColorName;
using Tetris::Config;
using Tetris::ConsoleMatrixDisplayImpl;
using Tetris::create_color;
using Tetris::GameController;
using Tetris::GameImpl;
using Tetris::GameState;
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
                create_color(ColorName::red),
                create_color(ColorName::green),
                create_color(ColorName::blue),
                create_color(ColorName::yellow),
                create_color(ColorName::purple),
                create_color(ColorName::orange),
                create_color(ColorName::pink),
            },
            1,
            true
        },
        {
            {64, 64},
            create_color(ColorName::white)
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
        config.game.generate_ghost
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
    ui.connect_hard_drop_pressed([&game](){ game.handle_hard_drop(); });
    ui.connect_hold_pressed([&game](){ game.handle_hold(); });
    ui.connect_pause_pressed([&game_controller](){
        game_controller.handle_pause_pressed();});

    int input;
    ::WINDOW * game_window{matrix.get_game_window()};
    
    while ((input = ::wgetch(game_window)) != 'q')
    {
        ui.input_received(input);
        if (game.get_state() == GameState::ended)
            game.game_over();
    }    
    return 0;
}