#ifndef INCLUDE_UI_CONSOLE_KEYBOARD_IMPL
#define INCLUDE_UI_CONSOLE_KEYBOARD_IMPL

#include "config/keyboard/console/config.h"
#include "ui/keyboard/keyboard.h"

#include <map>
#include <ncurses.h>

namespace Tetris::Ui
{

class ConsoleKeyboardImpl final: public Keyboard
{
public:
    ConsoleKeyboardImpl(::WINDOW* const window, const KeyboardConfig& config)
      : window_{window},
        config_{config}
    {
        ::keypad(window_, true);
    }

    int get_pressed_key_code() override
    {
        const int input{::wgetch(window_)};
        const auto it{config_.key_codes.find(input)};
        if (it != config_.key_codes.end())
            return it->second;
        return config_.no_key_code;
    }

private:
    ::WINDOW* const window_;
    KeyboardConfig config_;
};

} // namespace Tetris::Ui

#endif
