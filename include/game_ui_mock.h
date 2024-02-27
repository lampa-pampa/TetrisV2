#ifndef GAME_UI_MOCK_H
#define GAME_UI_MOCK_H

#include "brick.h"
#include "game_ui.h"
#include "pixel.h"
#include <vector>

class GameUIMock final: public GameUI
{
    public:
        void refresh_board(const std::vector<std::vector<Pixel>>& pixels) override{}
        void refresh_score(int score) override{}
        void refresh_tetrises(int tetrises) override{}
        void refresh_next(const Brick& brick) override{}
        void refresh_hold(const Brick& brick) override{}
};

#endif