#ifndef INCLUDE_GAME_UI_MOCK_H
#define INCLUDE_GAME_UI_MOCK_H

#include <vector>

#include "brick.h"
#include "game_ui.h"
#include "pixel.h"

namespace Tetris
{

class GameUiMock final: public GameUi
{
    using Pixels = std::vector<std::vector<Pixel>>;

public:
    void draw_board(const Pixels& pixels) override {}
    void draw_next(const Brick& brick) override {}
    void draw_hold(const Brick& brick) override {}
    void draw_score(unsigned long long score) override {}
    void draw_tetrises(unsigned long long tetrises) override {}
    void game_over() override {}
    void pause() override {}
    void resume() override {}
    void connect_move_left_pressed(std::function<void()> handler) override {}
    void connect_move_right_pressed(std::function<void()> handler) override {}
    void connect_rotate_pressed(std::function<void()> handler) override {}
    void connect_soft_drop_pressed(std::function<void()> handler) override {}
    void connect_hard_drop_pressed(std::function<void()> handler) override {}
    void connect_hold_pressed(std::function<void()> handler) override {}
    void connect_pause_pressed(std::function<void()> handler) override {}
};

}

#endif