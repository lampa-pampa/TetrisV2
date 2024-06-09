#ifndef INCLUDE_UI_GAME_UI_MOCK_H
#define INCLUDE_UI_GAME_UI_MOCK_H

#include <deque>
#include <vector>

#include "brick/brick.h"
#include "cube/cube.h"
#include "ui/game_ui/game_ui.h"

namespace Tetris::Ui
{

class GameUiMock final: public GameUi
{
public:
    void refresh_background() override {}
    void refresh_board(const CubeMatrix& cubes) override {}
    void refresh_cur_brick(const std::vector<Cube>& cubes) override {}
    void refresh_ghost_brick(const std::vector<Cube>& cubes) override {}
    void refresh_next_bricks(const std::deque<Brick>& bricks) override {}
    void refresh_hold_brick(const Brick& brick) override {}
    void refresh_score(unsigned long long score) override {}
    void refresh_level_progress_bar(int count) override {}
    void refresh_level(int level) override {}
    void flush_matrix() override {}
    void game_over() override {}
    void pause() override {}
    void resume() override {}
    void handle_key_press(int key_code) override {}
    void connect_move_left_pressed(
        const std::function<void()>& handler) override
    {}
    void connect_move_right_pressed(
        const std::function<void()>& handler) override
    {}
    void connect_rotate_clockwise_pressed(
        const std::function<void()>& handler) override
    {}
    void connect_rotate_counter_clockwise_pressed(
        const std::function<void()>& handler) override
    {}
    void connect_soft_drop_pressed(
        const std::function<void()>& handler) override
    {}
    void connect_locking_hard_drop_pressed(
        const std::function<void()>& handler) override
    {}
    void connect_no_locking_hard_drop_pressed(
        const std::function<void()>& handler) override
    {}
    void connect_hold_pressed(const std::function<void()>& handler) override {}
};

} // namespace Tetris::Ui

#endif
