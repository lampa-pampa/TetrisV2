#ifndef INCLUDE_UI_CONSOLE_INPUT_RECEIVER_IMPL
#define INCLUDE_UI_CONSOLE_INPUT_RECEIVER_IMPL

#include "ui/input_receiver/input_receiver.h"

#include <ncurses.h>

namespace Tetris::Ui
{

class ConsoleInputReceiverImpl final: public InputReceiver
{
public:
    ConsoleInputReceiverImpl(::WINDOW * const window)
    :
        window_{window}
    {
        ::keypad(window_, true);
    }

    int get_pressed_key_code() const override
    {
        return ::wgetch(window_);
    }

private:
    ::WINDOW * const window_;
};

}

#endif