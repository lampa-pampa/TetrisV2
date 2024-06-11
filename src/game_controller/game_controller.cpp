#include "game_controller/game_controller.h"

#include "game/game.h"
#include "game/state.h"
#include "game_controller/game_controller_key_codes.h"
#include "timer/timer.h"
#include "ui/keyboard/keyboard.h"

namespace Tetris
{

GameController::GameController(Game& game,
    Timer& timer,
    Ui::Keyboard& keyboard,
    GameControllerKeyCodes key_codes)
  : game_{game},
    timer_{timer},
    keyboard_{keyboard},
    key_codes_{key_codes}
{}

bool GameController::update(unsigned long delta_time)
{
    const GameState state{game_.get_state()};
    const int key_code{keyboard_.get_pressed_key_code()};

    if (timer_.is_active())
        timer_.update(delta_time);

    if (state == GameState::ended)
        end_game();
    else
        handle_key_press(key_code, state);

    return key_code != key_codes_.quit;
}

//--------------------------------------------------------------------

void GameController::handle_pause_pressed(GameState state)
{
    if (state == GameState::active)
        pause_game();
    else if (state == GameState::paused)
        start_game();
}

} // namespace Tetris
