#ifndef INCLUDE_UI_CONSOLE_MATRIX_DISPLAY_IMPL_H
#define INCLUDE_UI_CONSOLE_MATRIX_DISPLAY_IMPL_H

#include "matrix_display.h"

#include <vector>

#include <ncurses.h>

#include "iv_color.h"
#include "ncurses_colors.h"
#include "vector_2.h"

namespace Tetris::Ui
{

class ConsoleMatrixDisplayImpl final: public MatrixDisplay
{  
public:
    ConsoleMatrixDisplayImpl(
        Vector2 size,
        Vector2 pixel_size,
        int max_color_value,
        const std::vector<wchar_t>& pixel_chars,
        NCursesColors color_id_to_color);

    ~ConsoleMatrixDisplayImpl()
    {
        ::endwin();
    }

    void refresh(const IvColorMatrix& colors) override;

    Vector2 get_size() const override
    {
        return size_;
    }

    WINDOW * get_game_window() const
    {
        return window_;
    }

private:
    const Vector2 size_;
    const Vector2 pixel_size_;
    const std::vector<wchar_t> pixel_chars_;
    const int max_color_value_;

    ::WINDOW* window_;
    NCursesColors color_id_to_color_;

    Vector2 get_console_size() const;
    Vector2 compute_window_position() const;
    void create_window();
    void setup_ncurses_window();
    void setup_ncurses_keyboard();
    void print_colored(Vector2 position, int color, wchar_t pixel_char);
    void refresh_pixel(Vector2 position, IvColor color);
    wchar_t get_pixel_char(int color_value);

    Vector2 compute_window_size() const
    {
        return size_.scale(pixel_size_);
    }
};

}

#endif