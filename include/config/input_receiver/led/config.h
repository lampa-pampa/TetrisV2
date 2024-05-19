#ifndef INCLUDE_INPUT_RECEIVER_CONFIG_H
#define INCLUDE_INPUT_RECEIVER_CONFIG_H

#include <vector>

namespace Tetris
{

struct InputReceiverConfig final
{
    std::vector<int> row_pins;
    std::vector<int> column_pins;
    int no_key_code;
};

}

#endif