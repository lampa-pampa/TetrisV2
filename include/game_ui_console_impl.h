#ifndef GAME_UI_CONSOLE_IMPL_H
#define GAME_UI_CONSOLE_IMPL_H

#include "brick.h"
#include "color.h"
#include "game_ui.h"
#include "pixel.h"
#include <boost/signals2.hpp>
#include <functional>
#include <map>
#include <ncurses.h>
#include <string>
#include <vector>

class NCursesColors final
{
    const std::map<Color, int> color_to_ncurses_color
    {
        {Color::black, COLOR_BLACK},
        {Color::red, COLOR_RED},
        {Color::green, COLOR_GREEN},
        {Color::yellow, COLOR_YELLOW},
        {Color::blue, COLOR_BLUE},
        {Color::purple, COLOR_MAGENTA},
        {Color::orange, COLOR_MAGENTA},
        {Color::pink, COLOR_MAGENTA},
    };
    std::map<Color, int> color_to_pair;
    
public:
    int get_color_pair(Color color)
    {
        auto it = this->color_to_pair.find(color);
        if (it == this->color_to_pair.end())
        {
            const int ncurses_color{this->color_to_ncurses_color.at(color)};
            ::init_pair(ncurses_color, ncurses_color, COLOR_BLACK);
            it = this->color_to_pair.insert({color, ncurses_color}).first;
        }
        return it->second;
    }
};

class GameUIConsoleImpl final: public GameUI
{
    std::vector<std::vector<Pixel>> pixels{};
    NCursesColors ncurses_colors;
    const std::string title{"TETRIS"};
    const int pixel_width{2};
    const int pixel_height{1};
    const int border_width{1};
    const std::string empty_pixel{"  "};
    const std::string filled_pixel{"[]"};
    const std::string ghost_pixel{"::"};
    
    const std::map<int, boost::signals2::signal<void()>&> input_to_signal{
        {KEY_LEFT, this->move_left_pressed},
        {KEY_RIGHT, this->move_right_pressed},
        {KEY_UP, this->rotate_pressed},
        {KEY_DOWN, this->soft_drop_pressed},
        {' ', this->hard_drop_pressed},
        {'e', this->hold_pressed},
        {'p', this->handle_pause_pressed},
    };

    int width;
    int height;
    ::WINDOW* window;
    boost::signals2::signal<void()> move_left_pressed;
    boost::signals2::signal<void()> move_right_pressed;
    boost::signals2::signal<void()> rotate_pressed;
    boost::signals2::signal<void()> soft_drop_pressed;
    boost::signals2::signal<void()> hard_drop_pressed;
    boost::signals2::signal<void()> hold_pressed;
    boost::signals2::signal<void()> handle_pause_pressed;

    std::string get_pixel_as_text(const Pixel& pixel) const;
    void print_colored_str(std::string str, int x, int y, Color color);
    void create_window();
    void get_color_pair_index(Color color);

    int get_text_size(int size, int pixel_size) const
    {
        return size * pixel_size + 2 * this->border_width;
    }

    void print_str(std::string str, int x, int y)
    {
        mvwprintw(this->window, y, x, "%s", str.data());
    }

    void print_title()
    {
        int size{this->get_text_size(this->width, this->pixel_width)};
        int center_x = this->get_centered_index(size, this->title.size());
        this->print_str(this->title, center_x, 0);
    }

    void print_centered(std::string message)
    {
        int size{this->get_text_size(this->width, this->pixel_width)};
        int center_x = this->get_centered_index(size, message.size());
        int center_y = this->get_text_size(this->height, this->pixel_height) / 2;
        this->print_str(message, center_x, center_y);
    }

    int get_centered_index(int max_index, int content_size) const
    {
        return max_index / 2 - content_size / 2;
    }

public:
    GameUIConsoleImpl(int width, int height, NCursesColors& ncurses_colors);

    void refresh_board(const std::vector<std::vector<Pixel>>& pixels) override;
    void refresh_score(int score) override;
    void refresh_tetrises(int tetrises) override;
    void refresh_next(const Brick& brick) override;
    void refresh_hold(const Brick& brick) override;
    void input_received(int input);

    ~GameUIConsoleImpl()
    {
        endwin();
    }

    WINDOW * get_game_window()
    {
        return this->window;
    }

    void game_over() override
    {
        this->print_centered("GAME OVER!");
    }

    void pause() override
    {
        this->print_centered("GAME PAUSED");
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

#endif