#include "config/matrix_display/console/filled_config.h"

#include "config/matrix_display/console/config.h"
#include "ui/color/color_name.h"
#include "ui/color/console/ncurses_colors.h"

namespace Tetris::Ui
{

const MatrixDisplayConfig matrix_display_config{
    {64, 64}, // matrix size
    {2, 1}, // pixel size
    0xff, // max color value
    {
        // PIXEL CHARS
        L' ',
        L'·',
        L'◦',
        L'◌',
        L'○',
        L'◎',
        L'◉',
        L'●',
    },
    NCursesColors{{
        // COLOR TO NCURSES-ID
        {ColorName::black, 0},
        {ColorName::dark_candy_apple_red, 1},
        {ColorName::islamic_green, 2},
        {ColorName::windsor_tan, 3},
        {ColorName::duke_blue, 4},
        {ColorName::heliotrope_magenta, 5},
        {ColorName::tiffany_blue, 6},
        {ColorName::dark_gray, 7},
        {ColorName::davy_s_grey, 8},
        {ColorName::sunset_orange, 9},
        {ColorName::screamin_green, 10},
        {ColorName::dodie_yellow, 11},
        {ColorName::very_light_blue, 12},
        {ColorName::shocking_pink, 13},
        {ColorName::electric_blue, 14},
        {ColorName::white, 15},
    }},
};

}
