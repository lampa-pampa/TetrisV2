#ifndef INCLUDE_UI_INPUT_RECEIVER_H
#define INCLUDE_UI_INPUT_RECEIVER_H

namespace Tetris::Ui
{

class InputReciever
{
public:
    virtual int get_pressed_key_code() const = 0;
    ~InputReciever() = default;
};

}

#endif