#ifndef INCLUDE_GAME_UI_H
#define INCLUDE_GAME_UI_H

#include <vector>

#include "brick.h"
#include "pixel.h"

namespace Tetris
{

class GameUi
{
    using Pixels = std::vector<std::vector<Pixel>>;

public:
    virtual void refresh_board(const Pixels& pixels) = 0;
    virtual void refresh_next(const Brick& brick) = 0;
    virtual void refresh_hold(const Brick& brick) = 0;
    virtual void refresh_score(unsigned long long score) = 0;
    virtual void refresh_tetrises(unsigned long long tetrises) = 0;
    virtual void game_over() = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual ~GameUi() = default;
};

}

#endif