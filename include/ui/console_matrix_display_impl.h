#ifndef INCLUDE_UI_CONSOLE_MATRIX_DISPLAY_IMPL
#define INCLUDE_UI_CONSOLE_MATRIX_DISPLAY_IMPL

#include "matrix_display.h"

#include <cstdint>

#include <ncurses.h>

#include "ncurses_colors.h"
#include "vector_2.h"

namespace Tetris::Ui
{

class ConsoleMatrixDisplayImpl final: public MatrixDisplay
{  
public:
    ConsoleMatrixDisplayImpl(
        int width, int height, NCursesColors ncurses_colors);

    ~ConsoleMatrixDisplayImpl()
    {
        ::endwin();
    }

    void refresh(const ColorCodeMatrix& color_ids) override;

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

    Vector2 get_console_size() const;
    Vector2 compute_window_position() const;
    void create_window();
    void print_colored(Vector2 position, int ncurses_color);
    void refresh_pixel(Vector2 position, uint_fast8_t color_id);
    void setup_ncurses_window();
    void setup_ncurses_keyboard();

    Vector2 compute_window_size() const
    {
        return {this->width * pixel_width, this->height * pixel_height};
    }
};

}

#endif