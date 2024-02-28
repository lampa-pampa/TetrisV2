#ifndef GAME_UI_MOCK_H
#define GAME_UI_MOCK_H

#include "brick.h"
#include "game_ui.h"
#include "pixel.h"
#include <vector>

class GameUiMock final: public GameUi
{
public:
    void refresh_board(const std::vector<std::vector<Pixel>>& pixels) override{}
    void refresh_score(unsigned long long score) override{}
    void refresh_tetrises(unsigned long long tetrises) override{}
    void refresh_next(const Brick& brick) override{}
    void refresh_hold(const Brick& brick) override{}
    void game_over() override{}
    void pause() override{}
    void resume() override{}
};

#endif