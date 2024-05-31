#ifndef INCLUDE_UI_GAME_UI_H
#define INCLUDE_UI_GAME_UI_H

#include <functional>
#include <vector>

#include "brick/brick.h"
#include "cube/cube.h"

namespace Tetris::Ui
{

class GameUi
{
public:
    using CubeMatrix = std::vector<std::vector<Cube>>;

    virtual void refresh_board(const CubeMatrix& cubes) = 0;
    virtual void refresh_cur_brick(const std::vector<Cube>& cubes) = 0;
    virtual void refresh_ghost_brick(const std::vector<Cube>& cubes) = 0;
    virtual void refresh_next_brick(const Brick& brick) = 0;
    virtual void refresh_hold_brick(const Brick& brick) = 0;
    virtual void refresh_score(unsigned long long score) = 0;
    virtual void refresh_tetrises(unsigned long long tetrises) = 0;
    virtual void refresh_level_progress_bar(int quantity) = 0;
    virtual void refresh_level(int level) = 0;
    virtual void flush_matrix() = 0;
    virtual void game_over() = 0;
    virtual void pause() = 0;
    virtual void handle_key_press(int key_code) = 0;
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
    virtual void connect_hold_pressed(const std::function<void()>& handler) = 0;
    virtual ~GameUi() = default;
};

} // namespace Tetris::Ui

#endif
