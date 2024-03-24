#include "console_game_controller_impl.h"

#include <ncurses.h>

#include "game_state.h"
#include "game.h"
#include "timer.h"

namespace Tetris
{

ConsoleGameControllerImpl::ConsoleGameControllerImpl(
    Timer& timer,
    Game& game,
    ::WINDOW * window,
    int pause_key_code,
    int quit_key_code,
    int no_key_code)
:
    timer{timer},
    game{game},
    window{window},
    pause_key_code_{pause_key_code},
    quit_key_code_{quit_key_code},
    no_key_code_{no_key_code}
{}

void ConsoleGameControllerImpl::run()
{
    int key_code;
    timer.start();
    while ((key_code = ::wgetch(window)) != quit_key_code_)
    {
        const GameState state{game.get_state()};
        if (state == GameState::ended)
            end_game();
        else
            update(key_code, state);
    }
}

//--------------------------------------------------------------------

void ConsoleGameControllerImpl::handle_pause_pressed()
{
    const GameState state{game.get_state()};
    if (state == GameState::in_progress)
        pause_game();
    else if (state == GameState::paused)
        start_game();
}

}