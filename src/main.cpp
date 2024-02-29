#include "bag.h"
#include "board_impl.h"
#include "brick_generator_impl.h"
#include "brick_sources.h"
#include "color.h"
#include "color_sources.h"
#include "game_controller.h"
#include "game_impl.h"
#include "game_state.h"
#include "game_ui_console_impl.h"
#include "rng_impl.h"
#include "score_counter_impl.h"
#include "timer_mock.h"
#include "ncurses_colors.h"
#include <ncurses.h>

using namespace Tetris;

int main()
{
    TimerMock timer{};
    NCursesColors colors;
    GameUiConsoleImpl ui{10, 20, colors};
    BoardImpl board{10, 20};
    RngImpl rng{};
    BrickGeneratorImpl brick_generator{
        Bag<Brick>{brick_sources, rng},
        Bag<Color>{color_sources, rng}
    };
    ScoreCounterImpl score_counter{10, 1, 2};
    GameImpl game{ui, board, brick_generator, score_counter};
    GameController game_controller{timer, game};
    
    timer.connect_timeout([&game](){
        game.handle_tick();
    });

    ui.connect_move_left_pressed([&game](){
        if (game.get_state() == GameState::in_progress)
            game.handle_move_left();
    });

    ui.connect_move_right_pressed([&game](){
        if (game.get_state() == GameState::in_progress)
            game.handle_move_right();
    });


    ui.connect_rotate_pressed([&game](){
        if (game.get_state() == GameState::in_progress)
            game.handle_rotate();
    });

    ui.connect_soft_drop_pressed([&game](){
        if (game.get_state() == GameState::in_progress)
            game.handle_soft_drop();
    });

    ui.connect_hard_drop_pressed([&game](){
        if (game.get_state() == GameState::in_progress)
            game.handle_hard_drop();
    });

    ui.connect_hold_pressed([&game](){
        if (game.get_state() == GameState::in_progress)
            game.handle_hold();
    });

    ui.connect_pause_pressed([&game_controller](){
        game_controller.handle_pause_pressed();
    });

    int input;
    ::WINDOW * game_window{ui.get_game_window()};
    
    while((input = ::wgetch(game_window)) != 'q')
    {
        ui.input_received(input);

        const GameState state = game.get_state();
        if (state == GameState::ended)
            game.game_over();
    }    
    return 0;
}