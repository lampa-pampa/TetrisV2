#ifndef INCLUDE_UI_LED_KEYBOARD_IMPL
#define INCLUDE_UI_LED_KEYBOARD_IMPL

#include "ui/keyboard/keyboard.h"

#include <cassert>
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
      : column_pins_{config.column_pins},
        row_pins_{config.row_pins},
        no_key_code_{config.no_key_code},
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
        return no_key_code_;
    }

private:
    const std::vector<int> column_pins_;
    const std::vector<int> row_pins_;
    const int no_key_code_;
    std::vector<std::vector<bool>> key_states_;
    std::deque<int> pressed_keys_;

    int create_key_code(int x, int y) const
    {
        return column_pins_.size() * y + x;
    }

    void setup_pin_modes()
    {
        for (const auto& pin : row_pins_)
            ::pinMode(pin, OUTPUT);
        for (const auto& pin : column_pins_)
            ::pinMode(pin, INPUT_PULLDOWN);
    }

    void update_key_states()
    {
        for (const auto& y : boost::irange(row_pins_.size()))
        {
            ::digitalWrite(row_pins_[y], HIGH);
            update_keys_row_state(y);
            ::digitalWrite(row_pins_[y], LOW);
        }
    }

    void update_keys_row_state(int y)
    {
        for (const auto x : boost::irange(column_pins_.size()))
        {
            const bool new_state{::digitalRead(column_pins_[x]) == HIGH};
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
