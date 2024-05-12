#include "config/matrix_display/console/filled_matrix_config.h"

#include "config/matrix_display/console/matrix_config.h"
#include "ui/matrix_display/console/ncurses_colors.h"

namespace Tetris
{

const MatrixConfig matrix_config{
    {64, 64},
    {2, 1},
    0xff,
    {
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
        {0, 16},
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