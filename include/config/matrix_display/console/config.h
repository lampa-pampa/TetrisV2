#ifndef INCLUDE_CONSOLE_MATRIX_DISPLAY_CONFIG_H
#define INCLUDE_CONSOLE_MATRIX_DISPLAY_CONFIG_H

#include <vector>

#include "ui/color/console/ncurses_colors.h"
#include "vector2/vector2.h"

namespace Tetris::Ui
{

struct MatrixDisplayConfig final
{
    Vector2 size;
    Vector2 pixel_size;
    int max_color_value;
    const std::vector<wchar_t>& pixel_chars;
    NCursesColors ncurses_colors;
};

} // namespace Tetris::Ui

#endif
