#include "game_ui_console_impl.h"

#include <string>
#include <vector>

#include <boost/range/irange.hpp>
#include <ncurses.h>

#include "brick.h"
#include "color.h"
#include "pixel.h"
#include "vector_2.h"

namespace Tetris
{

using std::vector;
using std::string;
using boost::irange;

void GameUiConsoleImpl::create_window()
{
    int c_screen_width;
    int c_screen_height;
    getmaxyx(stdscr, c_screen_height, c_screen_width);
     
    int c_display_width{this->d_display_width * this->c_dot_width}; 
    int c_display_height{this->d_display_height * this->c_dot_height};
    int c_x{c_screen_width / 2 - c_display_width / 2};
    int c_y{c_screen_height / 2 - c_display_height / 2};
    this->window = ::newwin(
        c_display_height,
        c_display_width,
        c_y, c_x
    );
    ::refresh();
}

void GameUiConsoleImpl::set_pixel(int d_x, int d_y, Color color)
{
    const int pair_index{this->ncurses_colors.get_color_pair(color)};
    int c_x{d_x * this->c_dot_width};
    int c_y{d_y * this->c_dot_height};
    ::wattron(this->window, COLOR_PAIR(pair_index));
    ::mvwprintw(this->window, c_y, c_x, "▣");
    ::wattroff(this->window, COLOR_PAIR(pair_index));
}

void GameUiConsoleImpl::draw_border()
{
    int d_end_x{this->d_display_width - 1};
    int d_end_y{this->d_display_height - 1};
    int d_border_size = this->d_border_width - 1;
    int d_game_board_width{this->d_pixel_size * this->p_game_board_width};
    int d_center_x{d_game_board_width + this->d_border_width};

    this->draw_line(
        {0, 0},
        {d_end_x, d_border_size},
        this->border_color
    );
    this->draw_line(
        {0, 0},
        {d_border_size, d_end_y},
        this->border_color
    );
    this->draw_line(
        {d_end_x - d_border_size, 0},
        {d_end_x, d_end_y},
        this->border_color
    );
    this->draw_line(
        {0, d_end_y - d_border_size},
        {d_end_x, d_end_y},
        this->border_color
    );

    this->draw_line(
        {d_center_x, 0},
        {d_center_x + d_border_size, d_end_y},
        this->border_color
    );
}

void GameUiConsoleImpl::draw_line(Vector2 from, Vector2 to, Color color)
{
    for(const auto& y : irange<int>(from.y, to.y + 1))
    {
        for(const auto& x : irange<int>(from.x, to.x + 1))
            this->set_pixel(x, y, color);
    }
}

GameUiConsoleImpl::GameUiConsoleImpl(const NCursesColors& ncurses_colors)
:   
    ncurses_colors{ncurses_colors}
{
    ::setlocale(LC_ALL, "");
    ::initscr();
    ::noecho();
    ::cbreak();
    ::start_color();
    this->create_window();
    ::keypad(this->window, true);
    ::nodelay(this->window, true);
    
    this->draw_border();
}

void GameUiConsoleImpl::refresh_board(const vector<vector<Pixel>>& pixels)
{
    this->pixels = pixels;
    for (const auto& p_y : irange<int>(pixels.size()))
    {
        int d_pixel_start_y = this->d_pixel_size * p_y;
        for (const auto& p_x : irange<int>(pixels[0].size()))
        {
            int d_pixel_start_x = this->d_pixel_size * p_x;
            for(const auto& d_offset_y : irange(this->d_pixel_size))
            {
                for(const auto& d_offset_x : irange(this->d_pixel_size))
                {
                    Vector2 d_position{this->d_game_board_position};
                    int d_pixel_x{d_pixel_start_x + d_offset_x + d_position.x};
                    int d_pixel_y{d_pixel_start_y + d_offset_y + d_position.y};
                    this->set_pixel(
                        d_pixel_x,
                        d_pixel_y,
                        pixels[p_y][p_x].color
                    );
                }
            }
        }
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