#include "game_controller.h"
#include "game_state.h"

void GameController::handle_pause_pressed()
{
    const GameState game_state{this->game.get_state()};

    if (game_state == GameState::in_progress)
    {
        this->timer.stop();
        this->game.pause();
    }
    else if (game_state == GameState::paused)
    {
        this->timer.start();
        this->game.resume();
    }
}