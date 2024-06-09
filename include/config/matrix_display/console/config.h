#ifndef INCLUDE_CONSOLE_MATRIX_DISPLAY_CONFIG_H
#define INCLUDE_CONSOLE_MATRIX_DISPLAY_CONFIG_H

#include <vector>

#include "ui/color/console/ncurses_colors.h"
#include "vector_2/vector_2.h"

namespace Tetris
{

struct MatrixDisplayConfig final
{
    Vector2 size;
    Vector2 pixel_size;
    int max_color_value;
    const std::vector<wchar_t>& pixel_chars;
    Ui::NCursesColors ncurses_colors;
};

} // namespace Tetris

#endif
