#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "game.h"
#include "input_receiver.h"
#include "timer.h"
#include <memory>

class GameController
{
    std::unique_ptr<InputReceiver> input_receiver;
    std::unique_ptr<Timer> timer;
    std::unique_ptr<Game> game;

    public:
        GameController(
            std::unique_ptr<InputReceiver> &&input_receiver,
            std::unique_ptr<Timer> &&timer,
            std::unique_ptr<Game> &&game);
        void on_pause_pressed();
};

#endif