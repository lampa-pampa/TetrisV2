#ifndef INCLUDE_UI_KEYBOARD_H
#define INCLUDE_UI_KEYBOARD_H

namespace Tetris::Ui
{

class Keyboard
{
public:
    virtual int get_pressed_key_code() = 0;
    ~Keyboard() = default;
};

}

#endif