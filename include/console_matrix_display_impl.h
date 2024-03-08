#ifndef INCLUDE_CONSOLE_MATRIX_DISPLAY_IMPL
#define INCLUDE_CONSOLE_MATRIX_DISPLAY_IMPL

#include "matrix_display.h"

#include <ncurses.h>

#include <boost/range/irange.hpp>

#include "ncurses_colors.h"
#include "vector_2.h"

namespace Tetris
{

class ConsoleMatrixDisplayImpl final: public MatrixDisplay
{  
public:
    ConsoleMatrixDisplayImpl(
        int width,
        int height,
        NCursesColors ncurses_colors)
    :
        width{width},
        height{height},
        ncurses_colors{ncurses_colors}
    {
        this->setup_ncurses_window();
        this->setup_ncurses_keyboard();
    }

    ~ConsoleMatrixDisplayImpl()
    {
        ::endwin();
    }

    void refresh(const ColorCodeMatrix& color_codes) override
    {
        for (const auto& y : boost::irange(this->height))
        {
            for (const auto& x : boost::irange(this->width))
                this->refresh_pixel({x, y}, color_codes[y][x]);
        }
        ::wrefresh(this->window);
    }

    int get_width() const override
    {
        return this->width;
    }

    int get_height() const override
    {
        return this->height;
    }

    WINDOW * get_game_window() const
    {
        return this->window;
    }

private:
    static constexpr wchar_t pixel_char{L'◼'};
    static constexpr int pixel_width{2};
    static constexpr int pixel_height{1};

    const int width;
    const int height;

    ::WINDOW* window;
    NCursesColors ncurses_colors;

    Vector2 get_console_size() const
    {
        Vector2 size{};
        getmaxyx(stdscr, size.y, size.x);
        return size;
    }

    Vector2 compute_window_size() const
    {
        return {this->width * pixel_width, this->height * pixel_height};
    }

    Vector2 compute_window_position() const
    {
        const Vector2 console_size{this->get_console_size()};
        const Vector2 window_size{this->compute_window_size()};
        assert(console_size >= window_size);
        return {console_size / 2 - window_size / 2};
    }

    void create_window()
    {
        const Vector2 size{this->compute_window_size()};
        const Vector2 position{this->compute_window_position()};
        this->window = ::newwin(
            size.y, size.x, position.y, position.x);
        ::refresh();
    }

    void print_colored(Vector2 position, int ncurses_color)
    {
        ::wattron(this->window, COLOR_PAIR(ncurses_color));
        ::mvwprintw(this->window, position.y, position.x, "%lc", pixel_char);
        ::wattroff(this->window, COLOR_PAIR(ncurses_color));
    }

    void refresh_pixel(Vector2 position, int color_code)
    {
        const int ncurses_color{
            this->ncurses_colors.get_ncurses_color(color_code)
        };
        this->print_colored(
            position * Vector2{pixel_width, pixel_height}, ncurses_color);
    }

    void setup_ncurses_window()
    {
        ::setlocale(LC_ALL, "");
        ::initscr();
        ::start_color();
        this->create_window();
    }

    void setup_ncurses_keyboard()
    {
        ::keypad(this->window, true);
        ::noecho();
    }
};

}

#endif