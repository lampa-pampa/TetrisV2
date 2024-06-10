#include "config/keyboard/console/filled_config.h"

#include "config/keyboard/console/config.h"

namespace Tetris::Ui
{

const KeyboardConfig keyboard_config{
    {
        // KEY CODES
        {0x104, 13},
        {0x105, 15},
        {0x103, 10},
        {0x102, 14},
        {' ', 12},
        {'x', 8},
        {'z', 11},
        {'c', 9},
        {'p', 0},
        {'r', 3},
    },
    -1, // no key code
};

}
