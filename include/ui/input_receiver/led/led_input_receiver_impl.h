#ifndef INCLUDE_UI_LED_INPUT_RECEIVER_IMPL
#define INCLUDE_UI_LED_INPUT_RECEIVER_IMPL

#include "ui/input_receiver/input_receiver.h"

namespace Tetris::Ui
{

class LedInputReceiverImpl final: public InputReceiver
{
public:
    int get_pressed_key_code() const override
    {
        return -1;
    }
};

}

#endif