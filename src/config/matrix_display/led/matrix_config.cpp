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
        {0, {0x00, 0xff}},
        {1, {0x11, 0xff}},
        {2, {0x22, 0xff}},
        {3, {0x33, 0xff}},
        {4, {0x44, 0xff}},
        {5, {0x55, 0xff}},
        {6, {0x66, 0xff}},
        {7, {0x77, 0xff}},
        {8, {0x88, 0xff}},
        {9, {0x99, 0xff}},
        {10, {0xaa, 0xff}},
        {11, {0xbb, 0xff}},
        {12, {0xcc, 0xff}},
        {13, {0xdd, 0xff}},
        {14, {0xee, 0xff}},
        {15, {0xff, 0xff}},
    },
};

}