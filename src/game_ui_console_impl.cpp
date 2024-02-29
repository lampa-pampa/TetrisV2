#include "game_ui_console_impl.h"

#include <string>
#include <vector>

#include <ncurses.h>

#include "brick.h"
#include "color.h"
#include "pixel.h"

namespace Tetris
{

using std::vector;
using std::string;

void GameUiConsoleImpl::create_window()
{
    int screen_width;
    int screen_height;
    getmaxyx(stdscr, screen_height, screen_width);
     
    int x = screen_width / 2 - this->display_width;
    int y = screen_height / 2 - this->display_height / 2;
    this->window = ::newwin(this->display_height, this->display_width, y, x);
    ::refresh();
    ::keypad(this->window, true);
    ::nodelay(this->window, true);
}

void GameUiConsoleImpl::set_pixel(int x, int y, Color color)
{
    const int pair_index{this->ncurses_colors.get_color_pair(color)};
    ::wattron(this->window, COLOR_PAIR(pair_index));
    ::mvwprintw(this->window, y, x * 2, "[]");
    ::wattroff(this->window, COLOR_PAIR(pair_index));
}

GameUiConsoleImpl::GameUiConsoleImpl(const NCursesColors& ncurses_colors)
:   
    ncurses_colors{ncurses_colors}
{
    ::initscr();
    ::noecho();
    ::cbreak();
    ::start_color();
    this->create_window();
}

void GameUiConsoleImpl::refresh_board(const vector<vector<Pixel>>& pixels)
{
    this->pixels = pixels;
    for (const auto& row : pixels)
    {
        for (const auto& pixel : row)
            this->set_pixel(pixel.coords.x, pixel.coords.y, pixel.color);
    }
    ::wrefresh(this->window);
}

void GameUiConsoleImpl::refresh_score(unsigned long long score)
{

}

void GameUiConsoleImpl::refresh_tetrises(unsigned long long tetrises)
{

}

void GameUiConsoleImpl::refresh_next(const Brick& brick)
{

}

void GameUiConsoleImpl::refresh_hold(const Brick& brick)
{

}

void GameUiConsoleImpl::input_received(int input)
{
    if (auto it{this->input_to_signal.find(input)};
        it != this->input_to_signal.end()
    )
        it->second();
}

}