#ifndef INCLUDE_GAME_UI_H
#define INCLUDE_GAME_UI_H

#include <functional>
#include <vector>

#include "brick.h"
#include "cube.h"

namespace Tetris
{

class GameUi
{
public:
    using CubeMatrix = std::vector<std::vector<Cube>>;

    virtual void draw_board(const CubeMatrix& cubes) = 0;
    virtual void draw_cur_brick(const std::vector<Cube>& cubes) = 0;
    virtual void draw_ghost_brick(const std::vector<Cube>& cubes) = 0;
    virtual void draw_next_brick(const Brick& brick) = 0;
    virtual void draw_hold_brick(const Brick& brick) = 0;
    virtual void draw_score(unsigned long long score) = 0;
    virtual void draw_tetrises(unsigned long long tetrises) = 0;
    virtual void refresh() = 0;
    virtual void game_over() = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void input_received(int input) = 0;
    virtual void connect_move_left_pressed(
        const std::function<void()>& handler) = 0;
    virtual void connect_move_right_pressed(
        const std::function<void()>& handler) = 0;
    virtual void connect_rotate_clockwise_pressed(
        const std::function<void()>& handler) = 0;
    virtual void connect_rotate_counter_clockwise_pressed(
        const std::function<void()>& handler) = 0;
    virtual void connect_soft_drop_pressed(
        const std::function<void()>& handler) = 0;
    virtual void connect_locking_hard_drop_pressed(
        const std::function<void()>& handler) = 0;
    virtual void connect_no_locking_hard_drop_pressed(
        const std::function<void()>& handler) = 0;
    virtual void connect_hold_pressed(
        const std::function<void()>& handler) = 0;
    virtual void connect_pause_pressed(
        const std::function<void()>& handler) = 0;
    virtual ~GameUi() = default;
};

}

#endif