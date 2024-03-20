#ifndef INCLUDE_GAME_CONTROLLER_H
#define INCLUDE_GAME_CONTROLLER_H

#include "game_state.h"
#include "game.h"
#include "timer.h"

namespace Tetris
{

class GameController final
{
public:
    GameController(Timer& timer, Game& game)
    :
        timer{timer},
        game{game}
    {}
    
    void handle_pause_pressed()
    {
        const GameState state{this->game.get_state()};
        if (state == GameState::in_progress)
            this->pause_game();
        else if (state == GameState::paused)
            this->start_game();
    }

private:
    Timer& timer;
    Game& game;

    void pause_game()
    {
        this->timer.stop();
        this->game.pause();
    }

    void start_game()
    {
        this->timer.start();
        this->game.resume();
    }
};

}

#endif