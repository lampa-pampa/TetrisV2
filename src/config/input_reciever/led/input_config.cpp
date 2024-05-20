#include "config/input_receiver/led/filled_config.h"

#include "config/input_receiver/led/config.h"

namespace Tetris
{

const InputReceiverConfig input_receiver_config{
    {   // ROW PINS
        2,
        15,
        23,
        32,
    },
    {   // COLUMN PINS
        21,
        9,
        10,
        22,
    },
    -1, // no key code
};

}