#include "config/input_receiver/led/filled_input_config.h"

#include "config/input_receiver/led/input_config.h"

namespace Tetris
{

const InputConfig input_config{
    {   // COLUMN PINS
        21,
        9,
        10,
        22,
    },
    {   // ROW PINS
        2,
        15,
        23,
        32,
    },
    -1  // no key code
};

}