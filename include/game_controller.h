#ifndef INCLUDE_GAME_CONTROLLER_H
#define INCLUDE_GAME_CONTROLLER_H

#include "game.h"
#include "timer.h"

namespace Tetris
{

class GameController final
{
    Timer& timer;
    Game& game;

public:
    void handle_pause_pressed();

    GameController(Timer& timer, Game& game)
    :
        timer(timer),
        game(game)
    {}
};

}

#endif