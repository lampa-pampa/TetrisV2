#ifndef GAME_H
#define GAME_H

#include "game_state.h"

class Game
{
    public:
        virtual void set_state(GameState state) = 0;
        virtual GameState get_state() = 0;
        virtual void tick() = 0;
        virtual void move_left() = 0;
        virtual void move_right() = 0;
        virtual void rotate() = 0;
        virtual void soft_drop() = 0;
        virtual void hard_drop() = 0;
        virtual void hold_pressed() = 0;
        virtual ~Game() = default;
};

#endif