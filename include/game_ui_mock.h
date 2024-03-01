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
    void refresh_board(const Pixels& pixels) override{}
    void refresh_next(const Brick& brick) override{}
    void refresh_hold(const Brick& brick) override{}
    void refresh_score(unsigned long long score) override{}
    void refresh_tetrises(unsigned long long tetrises) override{}
    void game_over() override{}
    void pause() override{}
    void resume() override{}
};

}

#endif