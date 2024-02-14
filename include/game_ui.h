#ifndef GAME_UI_H
#define GAME_UI_H

#include "pixel.h"
#include <vector>

using std::vector;

class GameUI
{
    virtual void refresh_score(int score) = 0;
    virtual void refresh_board(vector<vector<Pixel>> pixels) = 0;
    virtual void refresh_tetrises(int tetrises) = 0;
};

#endif