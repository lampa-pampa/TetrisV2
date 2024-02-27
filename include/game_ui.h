#ifndef GAME_UI_H
#define GAME_UI_H

#include "brick.h"
#include "pixel.h"
#include <vector>

class GameUI
{
    public:
        virtual void refresh_board(const std::vector<std::vector<Pixel>>& pixels) = 0;
        virtual void refresh_score(int score) = 0;
        virtual void refresh_tetrises(int tetrises) = 0;
        virtual void refresh_next(const Brick& brick) = 0;
        virtual void refresh_hold(const Brick& brick) = 0;
        virtual ~GameUI() = default;
};

#endif