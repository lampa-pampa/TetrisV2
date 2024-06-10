#include "config/keyboard/led/filled_config.h"

#include "config/keyboard/led/config.h"

namespace Tetris::Ui
{

const KeyboardConfig keyboard_config{
    {
        // ROW PINS
        2,
        15,
        23,
        32,
    },
    {
        // COLUMN PINS
        21,
        9,
        10,
        22,
    },
    -1, // no key code
};

}
