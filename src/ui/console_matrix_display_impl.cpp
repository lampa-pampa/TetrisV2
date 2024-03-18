#include "ui/console_matrix_display_impl.h"

#include <cassert>

#include <boost/range/irange.hpp>
#include <ncurses.h>

#include "ui/iv_color.h"
#include "ui/ncurses_colors.h"
#include "vector_2.h"

using boost::irange;

namespace Tetris::Ui
{

ConsoleMatrixDisplayImpl::ConsoleMatrixDisplayImpl(
    int width, int height, NCursesColors ncurses_colors)
:
    width{width},
    height{height},
    ncurses_colors{ncurses_colors}
{
    this->setup_ncurses_window();
    this->setup_ncurses_keyboard();
}

void ConsoleMatrixDisplayImpl::refresh(const IvColorMatrix& iv_colors)
{
    for (const auto& y : irange(this->height))
    {
        for (const auto& x : irange(this->width))
            this->refresh_pixel({x, y}, iv_colors[y][x]);
    }
    ::wrefresh(this->window);
}

//-----------------------------------------------------------------------

Vector2 ConsoleMatrixDisplayImpl::get_console_size() const
{
    Vector2 size{};
    getmaxyx(stdscr, size.y, size.x);
    return size;
}

Vector2 ConsoleMatrixDisplayImpl::compute_window_position() const
{
    const Vector2 console_size{this->get_console_size()};
    const Vector2 window_size{this->compute_window_size()};
    assert(console_size >= window_size);
    return {console_size / 2 - window_size / 2};
}

void ConsoleMatrixDisplayImpl::create_window()
{
    const Vector2 size{this->compute_window_size()};
    const Vector2 position{this->compute_window_position()};
    this->window = ::newwin(
        size.y, size.x, position.y, position.x);
    ::refresh();
}

void ConsoleMatrixDisplayImpl::setup_ncurses_window()
{
    ::setlocale(LC_ALL, "");
    ::initscr();
    ::start_color();
    this->create_window();
}

void ConsoleMatrixDisplayImpl::setup_ncurses_keyboard()
{
    ::keypad(this->window, true);
    ::nodelay(this->window, true);
    ::noecho();
}

void ConsoleMatrixDisplayImpl::print_colored(
    Vector2 position, int color, wchar_t pixel_char)
{
    ::wattron(this->window, COLOR_PAIR(color));
    ::mvwprintw(this->window, position.y, position.x, "%lc", pixel_char);
    ::wattroff(this->window, COLOR_PAIR(color));
}

void ConsoleMatrixDisplayImpl::refresh_pixel(
    Vector2 position, IvColor iv_color)
{
    const int ncurses_color{
        this->ncurses_colors.get_ncurses_color(iv_color.id)
    };
    const wchar_t pixel_char{this->get_pixel_char(iv_color.value)};
    this->print_colored(
        position * Vector2{pixel_width, pixel_height},
        ncurses_color,
        pixel_char);
}

wchar_t ConsoleMatrixDisplayImpl::get_pixel_char(int color_value)
{
    return pixel_chars.at(color_value * pixel_chars.size() / max_color_value);
}

}