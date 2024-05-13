#include "config/matrix_display/led/filled_matrix_config.h"

#include "config/matrix_display/led/matrix_config.h"

namespace Tetris
{

const MatrixConfig matrix_config{
    {64, 64},
    160,
    1,
    {
        25, 26,
        27, 14,
        12, 13,
        0,  19,
        5,  17,
        33, 4,
        18, 16,
    },
    {
        {0, {0xff, 0xff}},
        {1, {0xff, 0xff}},
        {2, {0xff, 0xff}},
        {3, {0xff, 0xff}},
        {4, {0xff, 0xff}},
        {5, {0xff, 0xff}},
        {6, {0xff, 0xff}},
        {7, {0xff, 0xff}},
        {8, {0xff, 0xff}},
        {9, {0xff, 0xff}},
        {10, {0xff, 0xff}},
        {11, {0xff, 0xff}},
        {12, {0xff, 0xff}},
        {13, {0xff, 0xff}},
        {14, {0xff, 0xff}},
        {15, {0xff, 0xff}},
    },
};

}