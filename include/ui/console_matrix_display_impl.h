#ifndef INCLUDE_UI_CONSOLE_MATRIX_DISPLAY_IMPL_H
#define INCLUDE_UI_CONSOLE_MATRIX_DISPLAY_IMPL_H

#include "matrix_display.h"

#include <vector>

#include <ncurses.h>

#include "ncurses_colors.h"
#include "iv_color.h"
#include "vector_2.h"

namespace Tetris::Ui
{

class ConsoleMatrixDisplayImpl final: public MatrixDisplay
{  
public:
    ConsoleMatrixDisplayImpl(Vector2 size, NCursesColors color_id_to_color);

    ~ConsoleMatrixDisplayImpl()
    {
        ::endwin();
    }

    void refresh(const IvColorMatrix& colors) override;

    Vector2 get_size() const override
    {
        return this->size;
    }

    WINDOW * get_game_window() const
    {
        return this->window;
    }

private:
    static inline const std::vector<wchar_t> pixel_chars
    {   
        L' ',
        L'·',
        L'◦',
        L'◌',
        L'○',
        L'◎',
        L'◍',
        L'◉',
        L'●',
    };
    static constexpr int max_color_value{256};
    static constexpr Vector2 pixel_size{2, 1};

    const Vector2 size;

    ::WINDOW* window;
    NCursesColors color_id_to_color;

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
        return this->size.scale(pixel_size);
    }
};

}

#endif