#ifndef GAME_IMPL_H
#define GAME_IMPL_H

#include "game.h"
#include "game_state.h"

class GameImpl: public Game
{
    public:
        void set_state(GameState state);
        GameState get_state();
        void tick();
        void move_left();
        void move_right();
        void rotate();
        void soft_drop();
        void hard_drop();
        void hold_pressed();
};

#endif