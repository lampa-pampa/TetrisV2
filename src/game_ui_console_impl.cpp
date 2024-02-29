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
    
    int char_width{get_text_size(this->width, this->pixel_width)};
    int char_height{get_text_size(this->height, this->pixel_height)};    
    int center_x = this->get_centered_index(screen_width, char_width);
    int center_y = this->get_centered_index(screen_height, char_height);
    
    this->window = ::newwin(char_height, char_width, center_y, center_x);
    ::box(this->window, 0, 0);
    ::refresh();
    ::keypad(this->window, true);
    ::nodelay(this->window, true);
}

void GameUiConsoleImpl::print_colored_str(
    std::string str,
    int x,
    int y,
    Color color
){
    const int pair_index{this->ncurses_colors.get_color_pair(color)};
    ::wattron(this->window, COLOR_PAIR(pair_index));
    this->print_str(str, x, y);
    ::wattroff(this->window, COLOR_PAIR(pair_index));
}

string GameUiConsoleImpl::get_pixel_as_text(const Pixel& pixel) const
{
    if (not pixel.empty())
    {
        if (pixel.is_ghost)
            return this->ghost_pixel;
        else
            return this->filled_pixel;
    }
    else
    {
        return this->empty_pixel;
    }
}

GameUiConsoleImpl::GameUiConsoleImpl(
    int width, int height, const NCursesColors& ncurses_colors
):   
    ncurses_colors{ncurses_colors},
    width{width},
    height{height}
{
    ::initscr();
    ::noecho();
    ::cbreak();
    ::start_color();
    this->create_window();
    this->print_title();
}

void GameUiConsoleImpl::refresh_board(const vector<vector<Pixel>>& pixels)
{
    this->pixels = pixels;
    int y{border_width};
    for (const auto& row : pixels)
    {
        int x{border_width};
        for (const auto& it : row)
        {
            string text_pixel{this->get_pixel_as_text(it)};
            this->print_colored_str(text_pixel, x, y, it.color);
            x += this->pixel_width;
        }
        y += this->pixel_height;
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