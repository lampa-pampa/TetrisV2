#include "game_controller/game_controller.h"

#include "game_controller/game_controller_key_codes.h"
#include "game/game_state.h"
#include "game/game.h"
#include "timer/timer.h"

namespace Tetris
{

GameController::GameController(
    Timer& timer,
    Game& game,
    GameControllerKeyCodes key_codes)
:
    timer_{timer},
    game_{game},
    key_codes_{key_codes}
{}

bool GameController::update(unsigned long delta_time)
{
    const GameState state{game_.get_state()};
    const int key_code{get_pressed_key_code_().value()};
    
    if (timer_.is_active())
        timer_.update(delta_time);
    
    if(state == GameState::ended)
        end_game();
    else
        handle_key_press(key_code, state);
    
    return key_code != key_codes_.quit;
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