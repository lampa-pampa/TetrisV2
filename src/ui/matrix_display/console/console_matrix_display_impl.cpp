#include "ui/matrix_display/console/console_matrix_display_impl.h"

#include <cassert>

#include <boost/range/irange.hpp>
#include <ncurses.h>

#include "config/matrix_display/console/matrix_config.h"
#include "ui/color/iv_color.h"
#include "ui/matrix_display/console/ncurses_colors.h"
#include "vector_2/vector_2.h"

using boost::irange;

namespace Tetris::Ui
{

ConsoleMatrixDisplayImpl::ConsoleMatrixDisplayImpl(
    const MatrixConfig& config)
:
    size_{config.size},
    pixel_size_{config.pixel_size},
    pixel_chars_{config.pixel_chars},
    max_color_value_{config.max_color_value},
    ncurses_colors_{config.ncurses_colors}
{
    setup_ncurses_window();
}

void ConsoleMatrixDisplayImpl::refresh(const IvColorMatrix& colors)
{
    for (const auto& y : irange(size_.y))
    {
        for (const auto& x : irange(size_.x))
            refresh_pixel({x, y}, colors[y][x]);
    }
    ::wrefresh(window_);
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
    const Vector2 console_size{get_console_size()};
    const Vector2 window_size{compute_window_size()};
    assert(console_size >= window_size);
    return console_size.center() - window_size.center();
}

void ConsoleMatrixDisplayImpl::create_window()
{
    const Vector2 size{compute_window_size()};
    const Vector2 position{compute_window_position()};
    window_ = ::newwin(size.y, size.x, position.y, position.x);
    ::refresh();
}

void ConsoleMatrixDisplayImpl::setup_ncurses_window()
{
    ::setlocale(LC_ALL, "");
    ::initscr();
    ::start_color();
    create_window();
    ::nodelay(window_, true);
    ::noecho();
}

void ConsoleMatrixDisplayImpl::print_colored(
    Vector2 position, int color, wchar_t pixel_char)
{
    ::wattron(window_, COLOR_PAIR(color));
    ::mvwprintw(window_, position.y, position.x, "%lc", pixel_char);
    ::wattroff(window_, COLOR_PAIR(color));
}

void ConsoleMatrixDisplayImpl::refresh_pixel(Vector2 position, IvColor color)
{
    const int pixel_color{ncurses_colors_.get(color.id)};
    const wchar_t pixel_char{get_pixel_char(color.value)};
    print_colored(position.scale(pixel_size_), pixel_color, pixel_char);
}

wchar_t ConsoleMatrixDisplayImpl::get_pixel_char(int color_value)
{
    return pixel_chars_.at(
        color_value * pixel_chars_.size() / (max_color_value_ + 1));
}

}