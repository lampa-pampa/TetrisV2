#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "game.h"
#include "timer.h"

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

#endif