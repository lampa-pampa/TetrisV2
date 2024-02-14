#ifndef GAME_UI_H
#define GAME_UI_H

#include "pixel.h"
#include "brick.h"
#include <vector>

using std::vector;

class GameUI
{
    public:
        virtual void refresh_board(const vector<vector<Pixel>> &pixels) = 0;
        virtual void refresh_score(int score) = 0;
        virtual void refresh_tetrises(int tetrises) = 0;
        virtual void refresh_next(const Brick &brick) = 0;
        virtual void refresh_hold(const Brick &brick) = 0;
        virtual ~GameUI() = default;
};

#endif