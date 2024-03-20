#include "game_controller.h"

#include <ncurses.h>

#include "game_state.h"
#include "game.h"
#include "timer.h"

namespace Tetris
{

GameController::GameController(
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
    pause_key_code{pause_key_code},
    quit_key_code{quit_key_code},
    no_key_code{no_key_code}
{}

void GameController::run()
{
    int key_code;
    this->timer.start();
    while ((key_code = ::wgetch(this->window)) != this->quit_key_code)
    {
        const GameState state{this->game.get_state()};
        if (state == GameState::ended)
            this->end_game();
        else
            this->update(key_code, state);
    }
}

//--------------------------------------------------------------------

void GameController::handle_pause_pressed()
{
    const GameState state{this->game.get_state()};
    if (state == GameState::in_progress)
        this->pause_game();
    else if (state == GameState::paused)
        this->start_game();
}

}