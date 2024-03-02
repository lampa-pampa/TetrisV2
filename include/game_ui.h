#ifndef INCLUDE_GAME_UI_H
#define INCLUDE_GAME_UI_H

#include <functional>
#include <vector>

#include "brick.h"
#include "pixel.h"

namespace Tetris
{

class GameUi
{
    using Pixels = std::vector<std::vector<Pixel>>;

public:
    virtual void draw_game_board(const Pixels& pixels) = 0;
    virtual void draw_next(const Brick& brick) = 0;
    virtual void draw_hold(const Brick& brick) = 0;
    virtual void draw_score(unsigned long long score) = 0;
    virtual void draw_tetrises(unsigned long long tetrises) = 0;
    virtual void game_over() = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void connect_move_left_pressed(std::function<void()> handler) = 0;
    virtual void connect_move_right_pressed(std::function<void()> handler) = 0;
    virtual void connect_rotate_pressed(std::function<void()> handler) = 0;
    virtual void connect_soft_drop_pressed(std::function<void()> handler) = 0;
    virtual void connect_hard_drop_pressed(std::function<void()> handler) = 0;
    virtual void connect_hold_pressed(std::function<void()> handler) = 0;
    virtual void connect_pause_pressed(std::function<void()> handler) = 0;
    virtual ~GameUi() = default;
};

}

#endif