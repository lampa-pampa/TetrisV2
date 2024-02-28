#ifndef INCLUDE_GAME_UI_H
#define INCLUDE_GAME_UI_H

#include "brick.h"
#include "pixel.h"
#include <vector>

class GameUi
{
public:
    virtual void refresh_board(const std::vector<std::vector<Pixel>>& pixels) = 0;
    virtual void refresh_score(unsigned long long score) = 0;
    virtual void refresh_tetrises(unsigned long long tetrises) = 0;
    virtual void refresh_next(const Brick& brick) = 0;
    virtual void refresh_hold(const Brick& brick) = 0;
    virtual void game_over() = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual ~GameUi() = default;
};

#endif