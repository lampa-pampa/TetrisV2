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
    int width, int height, NCursesColors color_id_to_color)
:
    width{width},
    height{height},
    color_id_to_color{color_id_to_color}
{
    this->setup_ncurses_window();
    this->setup_ncurses_keyboard();
}

void ConsoleMatrixDisplayImpl::refresh(const IvColorMatrix& colors)
{
    for (const auto& y : irange(this->height))
    {
        for (const auto& x : irange(this->width))
            this->refresh_pixel({x, y}, colors[y][x]);
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
    return console_size.center() - window_size.center();
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

void ConsoleMatrixDisplayImpl::refresh_pixel(Vector2 position, IvColor color)
{
    const int pixel_color{
        this->color_id_to_color.get_ncurses_color(color.id)
    };
    const wchar_t pixel_char{this->get_pixel_char(color.value)};
    this->print_colored(
        position.scale({pixel_width, pixel_height}),
        pixel_color,
        pixel_char);
}

wchar_t ConsoleMatrixDisplayImpl::get_pixel_char(int color_value)
{
    return pixel_chars.at(color_value * pixel_chars.size() / max_color_value);
}

}