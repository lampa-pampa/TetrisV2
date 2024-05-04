#include "game_controller/game_controller.h"

#include <ncurses.h>

#include "game_controller/game_controller_key_codes.h"
#include "game/game_state.h"
#include "game/game.h"
#include "timer/timer.h"

namespace Tetris
{

GameController::GameController(
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

void GameController::run()
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

void GameController::handle_pause_pressed()
{
    const GameState state{game_.get_state()};
    if (state == GameState::in_progress)
        pause_game();
    else if (state == GameState::paused)
        start_game();
}

}