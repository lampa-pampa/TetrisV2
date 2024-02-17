#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "game.h"
#include "timer.h"

class GameController
{
    Timer &timer;
    Game &game;

    public:
        GameController(Timer &timer, Game &game);
        void on_pause_pressed();
};

#endif