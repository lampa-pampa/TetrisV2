#ifndef INCLUDE_CONSOLE_MATRIX_DISPLAY_IMPL
#define INCLUDE_CONSOLE_MATRIX_DISPLAY_IMPL

#include <vector>
#include <ncurses.h>

#include "matrix.h"
#include "ncurses_colors.h"

namespace Tetris
{

class ConsoleMatrixDisplayImpl final: public MatrixDisplay
{
    using ColorCodes = std::vector<std::vector<int>>;

    static constexpr wchar_t dot_char{L'◼'};
    static constexpr int pixel_width{2};
    static constexpr int pixel_height{1};

    const int width;
    const int height;

    ::WINDOW* window;
    NCursesColors ncurses_colors;

    void create_window();
    void refresh_pixel(int x, int y, int ncurses_color);
    
public:
    ConsoleMatrixDisplayImpl(
        int width,
        int height,
        NCursesColors ncurses_colors
    );
    ~ConsoleMatrixDisplayImpl()
    {
        ::endwin();
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

    void refresh(const ColorCodes& color_codes) override;

};

}

#endif