#ifndef GAME_UI_CONSOLE_IMPL_H
#define GAME_UI_CONSOLE_IMPL_H

#include "brick.h"
#include "game_ui.h"
#include "pixel.h"
#include <boost/signals2.hpp>
#include <functional>
#include <map>
#include <ncurses.h>
#include <vector>

class GameUIConsoleImpl final: public GameUI
{
    WINDOW *board;
    const std::map<int, boost::signals2::signal<void()> &> input_to_signal{
        {KEY_LEFT, this->move_left_pressed},
        {KEY_RIGHT, this->move_right_pressed},
        {KEY_UP, this->rotate_pressed},
        {KEY_DOWN, this->soft_drop_pressed},
        {' ', this->hard_drop_pressed},
        {'e', this->hold_pressed},
        {'p', this->pause_pressed},
    };
    boost::signals2::signal<void()> move_left_pressed;
    boost::signals2::signal<void()> move_right_pressed;
    boost::signals2::signal<void()> rotate_pressed;
    boost::signals2::signal<void()> soft_drop_pressed;
    boost::signals2::signal<void()> hard_drop_pressed;
    boost::signals2::signal<void()> hold_pressed;
    boost::signals2::signal<void()> pause_pressed;

    public:
        GameUIConsoleImpl(int width, int height);
        void refresh_board(const std::vector<std::vector<Pixel>> &pixels) override;
        void refresh_score(int score) override;
        void refresh_tetrises(int tetrises) override;
        void refresh_next(const Brick &brick) override;
        void refresh_hold(const Brick &brick) override;
        void input_received(int input);

        void connect_move_left_pressed(std::function<void()> handler)
        {
            this->move_left_pressed.connect(handler);
        }

        void connect_move_right_pressed(std::function<void()> handler)
        {
            this->move_right_pressed.connect(handler);
        }

        void connect_rotate_pressed(std::function<void()> handler)
        {
            this->rotate_pressed.connect(handler);
        }

        void connect_soft_drop_pressed(std::function<void()> handler)
        {
            this->soft_drop_pressed.connect(handler);
        }

        void connect_hard_drop_pressed(std::function<void()> handler)
        {
            this->hard_drop_pressed.connect(handler);
        }

        void connect_hold_pressed(std::function<void()> handler)
        {
            this->hold_pressed.connect(handler);
        }

        void connect_pause_pressed(std::function<void()> handler)
        {
            this->pause_pressed.connect(handler);
        }
};

#endif