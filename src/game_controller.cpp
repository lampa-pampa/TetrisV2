#include "game_controller.h"
#include "game_state.h"

void GameController::pause_pressed()
{
    switch(this->game.get_state())
    {
        case GameState::in_progress:
            this->timer.stop();
            this->game.set_state(GameState::paused);
            this->game.pause();
            break;
        case GameState::paused:
            this->timer.start();
            this->game.set_state(GameState::in_progress);
            this->game.resume();
            break;
        default:
            break;
    }
}