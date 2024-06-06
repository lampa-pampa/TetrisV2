#ifndef INCLUDE_CONSOLE_KEYBOARD_CONFIG_H
#define INCLUDE_CONSOLE_KEYBOARD_CONFIG_H

#include <map>

namespace Tetris
{

struct KeyboardConfig final
{
    std::map<int, int> key_codes;
    int no_key_code;
};

} // namespace Tetris

#endif
