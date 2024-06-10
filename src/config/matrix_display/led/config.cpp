#include "config/matrix_display/led/filled_config.h"

#include "config/matrix_display/led/config.h"
#include "ui/color/color_name.h"

namespace Tetris::Ui
{

const MatrixDisplayConfig matrix_display_config{
    {64, 64}, // size
    0x88, // brightness
    1, // chain length
    {
        // PINS
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
        // COLOR ID TO HS-COLOR
        {ColorName::black, {0x00, 0x00}},
        {ColorName::dark_candy_apple_red, {0x11, 0x88}},
        {ColorName::islamic_green, {0x22, 0x88}},
        {ColorName::windsor_tan, {0x33, 0x88}},
        {ColorName::duke_blue, {0x44, 0x88}},
        {ColorName::heliotrope_magenta, {0x55, 0x88}},
        {ColorName::tiffany_blue, {0x66, 0x88}},
        {ColorName::dark_gray, {0x77, 0x88}},
        {ColorName::davy_s_grey, {0x88, 0x88}},
        {ColorName::sunset_orange, {0x99, 0x88}},
        {ColorName::screamin_green, {0xaa, 0x88}},
        {ColorName::dodie_yellow, {0xbb, 0x88}},
        {ColorName::very_light_blue, {0xcc, 0x88}},
        {ColorName::shocking_pink, {0xdd, 0x88}},
        {ColorName::electric_blue, {0xee, 0x88}},
        {ColorName::white, {0x00, 0x00}},
    },
    0xff,
};

}
