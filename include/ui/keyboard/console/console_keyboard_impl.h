#ifndef INCLUDE_UI_CONSOLE_KEYBOARD_IMPL
#define INCLUDE_UI_CONSOLE_KEYBOARD_IMPL

#include "ui/keyboard/keyboard.h"

#include <ncurses.h>

namespace Tetris::Ui
{

class ConsoleKeyboardImpl final: public Keyboard
{
public:
    ConsoleKeyboardImpl(::WINDOW * const window)
    :
        window_{window}
    {
        ::keypad(window_, true);
    }

    int get_pressed_key_code() override
    {
        return ::wgetch(window_);
    }

private:
    ::WINDOW * const window_;
};

}

#endif