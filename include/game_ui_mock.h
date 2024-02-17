#ifndef GAME_UI_MOCK_H
#define GAME_UI_MOCK_H

#include "game_ui.h"

class GameUIMock: public GameUI
{
    public:
        void refresh_board(const vector<vector<Pixel>> &pixels) override;
        void refresh_score(int score) override;
        void refresh_tetrises(int tetrises) override;
        void refresh_next(const Brick &brick) override;
        void refresh_hold(const Brick &brick) override;
};

#endif