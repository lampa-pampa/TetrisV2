#include "console_game_controller_impl.h"

#include <ncurses.h>

#include "game_controller_key_codes.h"
#include "game_state.h"
#include "game.h"
#include "timer.h"

namespace Tetris
{

ConsoleGameControllerImpl::ConsoleGameControllerImpl(
    Timer& timer,
    Game& game,
    ::WINDOW * window,
    GameControllerKeyCodes key_codes)
:
    timer_{timer},
    game_{game},
    window_{window},
    key_codes_{key_codes}
    {}

void ConsoleGameControllerImpl::run()
{
    int key_code;
    timer_.start();
    while ((key_code = ::wgetch(window_)) != key_codes_.quit)
    {
        const GameState state{game_.get_state()};
        if (state == GameState::ended)
            end_game();
        else
            update(key_code, state);
    }
}

//--------------------------------------------------------------------

void ConsoleGameControllerImpl::handle_pause_pressed()
{
    const GameState state{game_.get_state()};
    if (state == GameState::in_progress)
        pause_game();
    else if (state == GameState::paused)
        start_game();
}

}