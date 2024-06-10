#include "config/matrix_display/led/filled_config.h"

#include "config/matrix_display/led/config.h"
#include "ui/color/color_name.h"

namespace Tetris::Ui
{

const MatrixDisplayConfig matrix_display_config{
    {64, 64}, // size
    128, // brightness
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
        {ColorName::dark_candy_apple_red, {0x0, 0xff}},
        {ColorName::islamic_green, {0x41, 0xf5}},
        {ColorName::windsor_tan, {0x23, 0xff}},
        {ColorName::duke_blue, {0x99, 0xae}},
        {ColorName::heliotrope_magenta, {0xd0, 0x59}},
        {ColorName::tiffany_blue, {0x81, 0xf5}},
        {ColorName::dark_gray, {0x40, 0x9}},
        {ColorName::davy_s_grey, {0x40, 0xb}},
        {ColorName::sunset_orange, {0x0, 0xd3}},
        {ColorName::screamin_green, {0x40, 0xc4}},
        {ColorName::dodie_yellow, {0x26, 0xaf}},
        {ColorName::very_light_blue, {0x97, 0x72}},
        {ColorName::shocking_pink, {0xda, 0x43}},
        {ColorName::electric_blue, {0x80, 0xc4}},
        {ColorName::white, {0x00, 0x00}},
    },
    0xff,
};

}
