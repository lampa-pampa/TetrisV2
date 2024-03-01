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
    int screen_width_chr;
    int screen_height_chr;
    getmaxyx(stdscr, screen_height_chr, screen_width_chr);
     
    int display_width_chr{this->display_width_dot * this->dot_width_chr}; 
    int display_height_chr{this->display_height_dot * this->dot_height_chr};
    int center_x_chr{screen_width_chr / 2 - display_width_chr / 2};
    int center_y_chr{screen_height_chr / 2 - display_height_chr / 2};
    this->window = ::newwin(
        display_height_chr,
        display_width_chr,
        center_y_chr,
        center_x_chr
    );
    ::refresh();
}

void GameUiConsoleImpl::set_pixel(int x_dot, int y_dot, Color color)
{
    const int pair_index{this->ncurses_colors.get_color_pair(color)};
    int x_chr{x_dot * this->dot_width_chr};
    int y_chr{y_dot * this->dot_height_chr};
    ::wattron(this->window, COLOR_PAIR(pair_index));
    ::mvwprintw(this->window, y_chr, x_chr, "%ls", &this->dot_char);
    ::wattroff(this->window, COLOR_PAIR(pair_index));
}

void GameUiConsoleImpl::draw_border()
{
    int max_x_dot{this->display_width_dot - 1};
    int max_y_dot{this->display_height_dot - 1};
    int max_border_width_dot = this->border_width_dot - 1;
    int board_width_dot{this->pixel_size_dot * this->board_width_px};
    int center_x_dot{board_width_dot + this->border_width_dot};

    this->draw_line(
        {0, 0},
        {max_x_dot, max_border_width_dot},
        this->border_color
    );
    this->draw_line(
        {0, 0},
        {max_border_width_dot, max_y_dot},
        this->border_color
    );
    this->draw_line(
        {max_x_dot - max_border_width_dot, 0},
        {max_x_dot, max_y_dot},
        this->border_color
    );
    this->draw_line(
        {0, max_y_dot - max_border_width_dot},
        {max_x_dot, max_y_dot},
        this->border_color
    );

    this->draw_line(
        {center_x_dot, 0},
        {center_x_dot + max_border_width_dot, max_y_dot},
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

void GameUiConsoleImpl::print_board(const vector<vector<Pixel>>& board, Vector2 position)
{
    for (const auto& y_px : irange<int>(board.size()))
    {
        int start_y_dot = this->pixel_size_dot * y_px;
        for (const auto& x_px : irange<int>(board[0].size()))
        {
            int start_x_dot = this->pixel_size_dot * x_px;
            this->print_pixel(start_x_dot, start_y_dot, board[y_px][x_px].color);
        }
    }
    ::wrefresh(this->window);
}

void GameUiConsoleImpl::print_pixel(int x_dot, int y_dot, Color color)
{
    for(const auto& offset_y_dot : irange(this->pixel_size_dot))
    {
        for(const auto& offset_x_dot : irange(this->pixel_size_dot))
        {
            this->set_pixel(
                x_dot + offset_x_dot + board_position_dot.x,
                y_dot + offset_y_dot + board_position_dot.y,
                color
            );
        }
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
    this->print_board(pixels, this->board_position_dot);
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