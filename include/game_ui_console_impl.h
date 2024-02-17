#ifndef GAME_UI_CONSOLE_IMPL_H
#define GAME_UI_CONSOLE_IMPL_H

#include "game_ui.h"
#include <boost/signals2.hpp>
#include <functional>

class GameUIConsoleImpl: public GameUI
{
    boost::signals2::signal<void()> move_left_pressed;
    boost::signals2::signal<void()> move_right_pressed;
    boost::signals2::signal<void()> rotate_pressed;
    boost::signals2::signal<void()> soft_drop_pressed;
    boost::signals2::signal<void()> hard_drop_pressed;
    boost::signals2::signal<void()> hold_pressed;
    boost::signals2::signal<void()> pause_pressed;

    public:
        void refresh_board(const vector<vector<Pixel>> &pixels) override;
        void refresh_score(int score) override;
        void refresh_tetrises(int tetrises) override;
        void refresh_next(const Brick &brick) override;
        void refresh_hold(const Brick &brick) override;

        void connect_move_left_pressed(std::function<void()> handler);
        void connect_move_right_pressed(std::function<void()> handler);
        void connect_rotate_pressed(std::function<void()> handler);
        void connect_soft_drop_pressed(std::function<void()> handler);
        void connect_hard_drop_pressed(std::function<void()> handler);
        void connect_hold_pressed(std::function<void()> handler);
        void connect_pause_pressed(std::function<void()> handler);
};

#endif