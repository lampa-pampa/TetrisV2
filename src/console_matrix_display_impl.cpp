#include "console_matrix_display_impl.h"

#include <boost/range/irange.hpp>

#include "ncurses_colors.h"
#include "vector_2.h"

namespace Tetris
{

using boost::irange;
using Tetris::ConsoleMatrixDisplayImpl;
constexpr wchar_t ConsoleMatrixDisplayImpl::pixel_char;

void ConsoleMatrixDisplayImpl::create_window()
{
    int console_width_chr;
    int console_height_chr;
    getmaxyx(stdscr, console_height_chr, console_width_chr);
    const int width_chr{this->width * cube_width};
    const int height_chr{this->width * cube_height};
    const int center_x_chr{console_width_chr / 2 - width_chr / 2};
    const int center_y_chr{console_height_chr / 2 - height_chr / 2};
    this->window = ::newwin(
        height_chr,
        width_chr,
        center_y_chr,
        center_x_chr);
    ::refresh();
}

void ConsoleMatrixDisplayImpl::refresh_pixel(
    Vector2 position,
    int ncurses_color)
{
    const int x_chr{position.x * cube_width};
    const int y_chr{position.y * cube_height};
    ::wattron(this->window, COLOR_PAIR(ncurses_color));
    ::mvwprintw(this->window, y_chr, x_chr, "%lc", pixel_char);
    ::wattroff(this->window, COLOR_PAIR(ncurses_color));
}

ConsoleMatrixDisplayImpl::ConsoleMatrixDisplayImpl(
    int width,
    int height,
    NCursesColors ncurses_colors)
:
    width{width},
    height{height},
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
}

void ConsoleMatrixDisplayImpl::refresh(const ColorCodeMatrix& color_codes)
{
    for (const auto& y : irange(this->height))
    {
        for (const auto& x : irange(this->width))
            this->refresh_pixel(
                {x, y},
                this->ncurses_colors.get_ncurses_color(color_codes[y][x]));
    }
    ::wrefresh(this->window);
}

}