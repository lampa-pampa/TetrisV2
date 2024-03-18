#ifndef INCLUDE_GAME_H
#define INCLUDE_GAME_H

#include <functional>

#include "game_state.h"

namespace Tetris
{

class Game
{
public:
    virtual void handle_rotate_clockwise() = 0;
    virtual void handle_rotate_counter_clockwise() = 0;
    virtual void handle_locking_hard_drop() = 0;
    virtual void handle_no_locking_hard_drop() = 0;
    virtual void handle_hold() = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void game_over() = 0;
    virtual void handle_timeout() = 0;
    virtual void handle_soft_drop() = 0;
    virtual GameState get_state() const = 0;
    virtual void handle_move_left() = 0;
    virtual void handle_move_right() = 0;
    virtual void connect_reset_timeout(
        const std::function<void()>& handler) = 0;
    virtual void connect_set_timeout_delay(
        const std::function<void(int)>& handler) = 0;
    virtual ~Game() = default;
};

}

#endif