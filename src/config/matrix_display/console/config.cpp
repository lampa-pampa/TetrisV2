#include "config/matrix_display/console/filled_config.h"

#include "config/matrix_display/console/config.h"
#include "ui/color/console/ncurses_colors.h"

namespace Tetris
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
    Ui::NCursesColors{{
        // COLOR TO NCURSES-ID
        {0, 0},
        {1, 1},
        {2, 2},
        {3, 3},
        {4, 4},
        {5, 5},
        {6, 6},
        {7, 7},
        {8, 8},
        {9, 9},
        {10, 10},
        {11, 11},
        {12, 12},
        {13, 13},
        {14, 14},
        {15, 15},
    }},
};

}
