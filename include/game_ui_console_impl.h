#ifndef INCLUDE_GAME_UI_CONSOLE_IMPL_H
#define INCLUDE_GAME_UI_CONSOLE_IMPL_H

#include <functional>
#include <map>
#include <vector>

#include <boost/signals2.hpp>
#include <ncurses.h>

#include "brick.h"
#include "color.h"
#include "game_ui.h"
#include "ncurses_colors.h"
#include "pixel.h"

namespace Tetris
{

class GameUiConsoleImpl final: public GameUi
{
    using signal = boost::signals2::signal<void()>;

    const int pixel_size{3};
    const int display_width{64};
    const int display_height{64};
    const std::map<int, signal&> input_to_signal{
        {KEY_LEFT, this->move_left_pressed},
        {KEY_RIGHT, this->move_right_pressed},
        {KEY_UP, this->rotate_pressed},
        {KEY_DOWN, this->soft_drop_pressed},
        {' ', this->hard_drop_pressed},
        {'c', this->hold_pressed},
        {'p', this->handle_pause_pressed},
    };
    int width;
    int height;
    std::vector<std::vector<Pixel>> pixels{};
    NCursesColors ncurses_colors;
    ::WINDOW* window;
    signal move_left_pressed;
    signal move_right_pressed;
    signal rotate_pressed;
    signal soft_drop_pressed;
    signal hard_drop_pressed;
    signal hold_pressed;
    signal handle_pause_pressed;

    void create_window();
    void set_pixel(int x, int y, Color color);

public:
    GameUiConsoleImpl(const NCursesColors& ncurses_colors);
    
    ~GameUiConsoleImpl()
    {
        ::endwin();
    }

    void refresh_board(const std::vector<std::vector<Pixel>>& pixels) override;
    void refresh_score(unsigned long long score) override;
    void refresh_tetrises(unsigned long long tetrises) override;
    void refresh_next(const Brick& brick) override;
    void refresh_hold(const Brick& brick) override;
    void input_received(int input);

    WINDOW * get_game_window()
    {
        return this->window;
    }

    void game_over() override
    {
        
    }

    void pause() override
    {
        
    }

    void resume() override
    {
        this->refresh_board(this->pixels);
    }

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
        this->handle_pause_pressed.connect(handler);
    }
};

}

#endif