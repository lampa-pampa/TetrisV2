#include "game_controller.h"
#include "timer.h"
#include "game.h"
#include "game_state.h"

GameController::GameController(Timer &timer, Game &game)
:
    timer(timer),
    game(game)
{}

void GameController::pause_pressed()
{
    switch (this->game.get_state())
    {
        case GameState::in_progress:
            this->timer.stop();
            this->game.set_state(GameState::paused);
        break;
        case GameState::paused:
            this->timer.start();
            this->game.set_state(GameState::in_progress);
        break;
        default:
        break;
    }
}