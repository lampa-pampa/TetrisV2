#ifndef INCLUDE_LED_KEYBOARD_CONFIG_H
#define INCLUDE_LED_KEYBOARD_CONFIG_H

#include <map>
#include <vector>

namespace Tetris
{

struct KeyboardConfig final
{
    std::vector<int> row_pins;
    std::vector<int> column_pins;
    std::map<int, int> key_index_to_key_code;
    int no_key_code;
};

} // namespace Tetris

#endif
