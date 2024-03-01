#include "matrix_game_ui_impl.h"

#include <string>
#include <vector>

#include <boost/range/irange.hpp>
#include <ncurses.h>

#include "color.h"
#include "pixel.h"
#include "vector_2.h"

namespace Tetris
{

using std::vector;
using std::string;
using boost::irange;
using Pixels = vector<vector<Pixel>>;
constexpr wchar_t MatrixGameUiImpl::dot_char;

void MatrixGameUiImpl::create_window()
{
    int screen_width_chr;
    int screen_height_chr;
    getmaxyx(stdscr, screen_height_chr, screen_width_chr);
    const int center_x_chr{screen_width_chr / 2 - display_width_chr / 2};
    const int center_y_chr{screen_height_chr / 2 - display_height_chr / 2};
    this->window = ::newwin(
        display_height_chr,
        display_width_chr,
        center_y_chr,
        center_x_chr
    );
    ::refresh();
}

void MatrixGameUiImpl::set_pixel(int x_dot, int y_dot, Color color)
{
    const int pair_index{this->ncurses_colors.get_color_pair(color)};
    const int x_chr{x_dot * dot_width_chr};
    const int y_chr{y_dot * dot_height_chr};
    ::wattron(this->window, COLOR_PAIR(pair_index));
    ::mvwprintw(this->window, y_chr, x_chr, "%lc", dot_char);
    ::wattroff(this->window, COLOR_PAIR(pair_index));
}

void MatrixGameUiImpl::draw_border()
{
    this->draw_line(
        {0, 0},
        {max_x_dot, max_border_width_dot},
        border_color
    );
    this->draw_line(
        {0, 0},
        {max_border_width_dot, max_y_dot},
        border_color
    );
    this->draw_line(
        {max_x_dot - max_border_width_dot, 0},
        {max_x_dot, max_y_dot},
        border_color
    );
    this->draw_line(
        {0, max_y_dot - max_border_width_dot},
        {max_x_dot, max_y_dot},
        border_color
    );

    this->draw_line(
        {center_x_dot, 0},
        {center_x_dot + max_border_width_dot, max_y_dot},
        border_color
    );
}

void MatrixGameUiImpl::draw_line(Vector2 from, Vector2 to, Color color)
{
    for (const auto& y : irange(from.y, to.y + 1))
    {
        for (const auto& x : irange(from.x, to.x + 1))
            this->set_pixel(x, y, color);
    }
}

void MatrixGameUiImpl::print_board(const Pixels& board, Vector2 position)
{
    for (const auto& y_px : irange<int>(board.size()))
    {
        const int start_y_dot{
            pixel_size_dot * y_px + board_position_dot.y
        };
        for (const auto& x_px : irange<int>(board[0].size()))
        {
            const int start_x_dot{
                pixel_size_dot * x_px + board_position_dot.x
            };
            const Color color{board[y_px][x_px].color};
            this->print_pixel(start_x_dot, start_y_dot, color);
        }
    }
    ::wrefresh(this->window);
}

void MatrixGameUiImpl::print_pixel(
    int start_x_dot,
    int start_y_dot,
    Color color
){
    for (const auto& offset_y_dot : irange(pixel_size_dot))
    {
        for (const auto& offset_x_dot : irange(pixel_size_dot))
        {
            const int x_dot{start_x_dot + offset_x_dot};
            const int y_dot{start_y_dot + offset_y_dot};
            this->set_pixel(x_dot, y_dot, color);
        }
    }
}

MatrixGameUiImpl::MatrixGameUiImpl(const NCursesColors& ncurses_colors)
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

void MatrixGameUiImpl::draw_board(const Pixels& pixels)
{
    this->game_board_pixels = pixels;
    this->print_board(pixels, board_position_dot);
}

void MatrixGameUiImpl::draw_next(const Brick& brick)
{

}

void MatrixGameUiImpl::draw_hold(const Brick& brick)
{

}

void MatrixGameUiImpl::draw_score(unsigned long long score)
{

}

void MatrixGameUiImpl::draw_tetrises(unsigned long long tetrises)
{

}

void MatrixGameUiImpl::input_received(int input)
{
    if (auto it{this->input_to_signal.find(input)};
        it != this->input_to_signal.end()
    )
        it->second();
}

}