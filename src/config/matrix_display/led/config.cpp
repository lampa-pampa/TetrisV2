#include "config/matrix_display/led/filled_config.h"

#include "config/matrix_display/led/config.h"

namespace Tetris
{

const MatrixDisplayConfig matrix_display_config{
    {64, 64},   // size
    0x88,        // brightness
    1,          // chain length
    {   // PINS
        25, 26,
        27, 14,
        12, 13,
        0,  19,
        5,  17,
        33, 4,
        18, 16,
    },
    {   // COLOR ID TO HS-COLOR
        {0, {0x00, 0x00}},
        {1, {0x11, 0x88}},
        {2, {0x22, 0x88}},
        {3, {0x33, 0x88}},
        {4, {0x44, 0x88}},
        {5, {0x55, 0x88}},
        {6, {0x66, 0x88}},
        {7, {0x77, 0x88}},
        {8, {0x88, 0x88}},
        {9, {0x99, 0x88}},
        {10, {0xaa, 0x88}},
        {11, {0xbb, 0x88}},
        {12, {0xcc, 0x88}},
        {13, {0xdd, 0x88}},
        {14, {0xee, 0x88}},
        {15, {0x00, 0x00}},
    },
};

}