#include "ui/matrix_display/led/config/filled_matrix_config.h"

#include "ui/matrix_display/led/config/matrix_config.h"

namespace Tetris
{

const MatrixConfig matrix_config{
    {64, 64},
    160,
    1,
    {
        25,
        26,
        27,
        14,
        12,
        13,
        0,
        19,
        5,
        17,
        33,
        4,
        18,
        16,
    },
    {
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
    },
};

}