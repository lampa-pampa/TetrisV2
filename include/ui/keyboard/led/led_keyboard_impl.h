#ifndef INCLUDE_UI_LED_KEYBOARD_IMPL
#define INCLUDE_UI_LED_KEYBOARD_IMPL

#include "ui/keyboard/keyboard.h"

#include <cstddef>
#include <deque>
#include <vector>

#include <Arduino.h>
#include <boost/range/irange.hpp>

#include "config/keyboard/led/config.h"

namespace Tetris::Ui
{

class LedKeyboardImpl final: public Keyboard
{
public:
    LedKeyboardImpl(const KeyboardConfig& config)
      : config_{config},
        key_states_{config.row_pins.size(),
            std::vector<bool>(config.column_pins.size())}
    {
        setup_pin_modes();
    }

    int get_pressed_key_code() override
    {
        update_key_states();
        if (not pressed_keys_.empty())
        {
            const int pressed_key{pressed_keys_.front()};
            pressed_keys_.pop_front();
            return pressed_key;
        }
        return config_.no_key_code;
    }

private:
    const KeyboardConfig& config_;
    std::vector<std::vector<bool>> key_states_;
    std::deque<int> pressed_keys_;

    int create_key_code(int x, int y) const
    {
        const size_t key_index{config_.column_pins.size() * y + x};
        return config_.key_index_to_key_code.at(key_index);
    }

    void setup_pin_modes()
    {
        for (const auto& pin : config_.row_pins)
            ::pinMode(pin, OUTPUT);
        for (const auto& pin : config_.column_pins)
            ::pinMode(pin, INPUT_PULLDOWN);
    }

    void update_key_states()
    {
        for (const auto& y : boost::irange(config_.row_pins.size()))
        {
            ::digitalWrite(config_.row_pins[y], HIGH);
            update_keys_row_state(y);
            ::digitalWrite(config_.row_pins[y], LOW);
        }
    }

    void update_keys_row_state(int y)
    {
        for (const auto x : boost::irange(config_.column_pins.size()))
        {
            const bool new_state{::digitalRead(config_.column_pins[x]) == HIGH};
            update_key_state(x, y, new_state);
        }
    }

    void update_key_state(int x, int y, bool new_state)
    {
        if (key_states_[y][x] != new_state)
        {
            if (new_state)
                pressed_keys_.emplace_back(create_key_code(x, y));
            key_states_[y][x] = new_state;
        }
    }
};

} // namespace Tetris::Ui

#endif
