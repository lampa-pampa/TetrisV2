#include "config/keyboard/led/filled_config.h"

#include "config/keyboard/led/config.h"

namespace Tetris::Ui
{

const KeyboardConfig keyboard_config{
    {
        // ROW PINS
        2,
        9,
        10,
        15,
    },
    {
        // COLUMN PINS
        21,
        22,
        23,
        32,
    },
    -1, // no key code
};

}
