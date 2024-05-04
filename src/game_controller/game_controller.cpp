#include "game_controller/game_controller.h"

#include <functional>

#include "game_controller/game_controller_key_codes.h"
#include "game/game_state.h"
#include "game/game.h"
#include "timer/timer.h"

using std::function;

namespace Tetris
{

GameController::GameController(
    Timer& timer,
    Game& game,
    const function<int()>& get_pressed_key_code,
    GameControllerKeyCodes key_codes)
:
    timer_{timer},
    game_{game},
    get_pressed_key_code_{get_pressed_key_code},
    key_codes_{key_codes}
    {}

void GameController::run()
{
    int key_code;
    timer_.start();
    while ((key_code = get_pressed_key_code_()) != key_codes_.quit)
    {
        const GameState state{game_.get_state()};
        if (state == GameState::ended)
            end_game();
        else
            update(key_code, state);
    }
}

//--------------------------------------------------------------------

void GameController::handle_pause_pressed(GameState state)
{
    if (state == GameState::in_progress)
        pause_game();
    else if (state == GameState::paused)
        start_game();
}

}