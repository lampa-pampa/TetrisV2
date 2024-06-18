#include "ui/keyboard/led/led_keyboard_impl.h"

#include <vector>

#include <Arduino.h>
#include <boost/range/irange.hpp>

#include "config/keyboard/led/config.h"

using boost::irange;
using std::vector;

namespace Tetris::Ui
{

LedKeyboardImpl::LedKeyboardImpl(const KeyboardConfig& config)
  : config_{config},
    key_states_{config.row_pins.size(), vector<bool>(config.column_pins.size())}
{
    setup_pin_modes();
}

int LedKeyboardImpl::get_pressed_key_code()
{
    update_key_states();
    if (pressed_keys_.empty())
        return config_.no_key_code;

    const int pressed_key{pressed_keys_.front()};
    pressed_keys_.pop_front();
    return pressed_key;
}

//--------------------------------------------------

void LedKeyboardImpl::setup_pin_modes()
{
    for (const auto& pin : config_.row_pins)
        ::pinMode(pin, OUTPUT);
    for (const auto& pin : config_.column_pins)
        ::pinMode(pin, INPUT_PULLDOWN);
}

void LedKeyboardImpl::update_key_states()
{
    for (const auto& y : irange(config_.row_pins.size()))
    {
        ::digitalWrite(config_.row_pins[y], HIGH);
        update_keys_row_state(y);
        ::digitalWrite(config_.row_pins[y], LOW);
    }
}

void LedKeyboardImpl::update_keys_row_state(int y)
{
    for (const auto x : irange(config_.column_pins.size()))
    {
        const bool new_state{::digitalRead(config_.column_pins[x]) == HIGH};
        update_key_state(x, y, new_state);
    }
}

void LedKeyboardImpl::update_key_state(int x, int y, bool new_state)
{
    if (key_states_[y][x] != new_state)
    {
        if (new_state)
            pressed_keys_.emplace_back(create_key_code(x, y));
        key_states_[y][x] = new_state;
    }
}

} // namespace Tetris::Ui
