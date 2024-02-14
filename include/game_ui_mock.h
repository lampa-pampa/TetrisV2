#ifndef GAME_UI_MOCK_H
#define GAME_UI_MOCK_H

#include "game_ui.h"

class GameUIMock: public GameUI
{
    public:
        void refresh_board(const vector<vector<Pixel>> &pixels);
        void refresh_score(int score);
        void refresh_tetrises(int tetrises);
        void refresh_next(const Brick &brick);
        void refresh_hold(const Brick &brick);
};

#endif