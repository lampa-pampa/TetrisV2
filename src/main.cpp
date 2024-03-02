#include <ncurses.h>

#include "bag.h"
#include "board_impl.h"
#include "brick_generator_impl.h"
#include "brick_sources.h"
#include "color_sources.h"
#include "game_controller.h"
#include "game_impl.h"
#include "game_state.h"
#include "matrix_game_ui_impl.h"
#include "ncurses_colors.h"
#include "rng_impl.h"
#include "score_counter_impl.h"
#include "timer_mock.h"

using Tetris::Bag;
using Tetris::BoardImpl;
using Tetris::brick_sources;
using Tetris::BrickGeneratorImpl;
using Tetris::color_sources;
using Tetris::GameController;
using Tetris::GameImpl;
using Tetris::GameState;
using Tetris::MatrixGameUiImpl;
using Tetris::NCursesColors;
using Tetris::RngImpl;
using Tetris::ScoreCounterImpl;
using Tetris::TimerMock;

int main()
{
    TimerMock timer{};
    NCursesColors colors;
    MatrixGameUiImpl ui{colors};
    BoardImpl board{10, 20};
    RngImpl rng{};
    BrickGeneratorImpl brick_generator{
        Bag{brick_sources, rng},
        Bag{color_sources, rng}
    };
    ScoreCounterImpl score_counter{10, 1, 2};
    GameImpl game{ui, board, brick_generator, score_counter};
    GameController game_controller{timer, game};
    
    timer.connect_timeout([&game](){ game.handle_timeout(); });
    ui.connect_move_left_pressed([&game](){ game.handle_move_left(); });
    ui.connect_move_right_pressed([&game](){ game.handle_move_right(); });
    ui.connect_rotate_pressed([&game](){ game.handle_rotate(); });
    ui.connect_soft_drop_pressed([&game](){ game.handle_soft_drop(); });
    ui.connect_hard_drop_pressed([&game](){ game.handle_hard_drop(); });
    ui.connect_hold_pressed([&game](){ game.handle_hold(); });
    ui.connect_pause_pressed([&game_controller](){
        game_controller.handle_pause_pressed();
    });

    int input;
    ::WINDOW * game_window{ui.get_game_window()};
    
    while ((input = ::wgetch(game_window)) != 'q')
    {
        ui.input_received(input);

        const GameState state{game.get_state()};
        if (state == GameState::ended)
            game.game_over();
    }    
    return 0;
}