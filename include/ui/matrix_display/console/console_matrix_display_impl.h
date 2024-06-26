#ifndef INCLUDE_UI_CONSOLE_MATRIX_DISPLAY_IMPL_H
#define INCLUDE_UI_CONSOLE_MATRIX_DISPLAY_IMPL_H

#include "ui/matrix_display/matrix_display.h"

#include <vector>

#include <ncurses.h>

#include "config/matrix_display/console/config.h"
#include "ui/color/console/ncurses_colors.h"
#include "ui/color/nv_color.h"
#include "vector2/vector2.h"

namespace Tetris::Ui
{

class ConsoleMatrixDisplayImpl final: public MatrixDisplay
{
public:
    ConsoleMatrixDisplayImpl(const MatrixDisplayConfig& config);

    ~ConsoleMatrixDisplayImpl()
    {
        ::endwin();
    }

    void refresh(const NvColorMatrix& buffer) override;

    Vector2 get_size() const override
    {
        return size_;
    }

    ::WINDOW* const get_window()
    {
        return window_;
    }

private:
    const Vector2 size_;
    const Vector2 pixel_size_;
    const std::vector<wchar_t> pixel_chars_;
    const int max_color_value_;

    ::WINDOW* window_;
    NCursesColors ncurses_colors_;

    Vector2 get_console_size() const;
    Vector2 compute_window_position() const;
    void create_window();
    void setup_ncurses_window();
    void setup_ncurses_keyboard();
    void print_colored(Vector2 position, int color, wchar_t pixel_char);
    void refresh_pixel(Vector2 position, NvColor color);
    wchar_t get_pixel_char(int color_value);

    Vector2 compute_window_size() const
    {
        return size_.scale(pixel_size_);
    }
};

} // namespace Tetris::Ui

#endif
