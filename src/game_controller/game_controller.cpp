#include "game_controller/game_controller.h"

#include "game_controller/game_controller_key_codes.h"
#include "game/game_state.h"
#include "game/game.h"
#include "timer/timer.h"
#include "ui/input_receiver/input_receiver.h"

namespace Tetris
{

GameController::GameController(
    Game& game,
    Timer& timer,
    Ui::InputReceiver& input_receiver,
    GameControllerKeyCodes key_codes)
:
    game_{game},
    timer_{timer},
    input_receiver_{input_receiver},
    key_codes_{key_codes}
{}

bool GameController::update(unsigned long delta_time)
{
    const GameState state{game_.get_state()};
    const int key_code{input_receiver_.get_pressed_key_code()};
    
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