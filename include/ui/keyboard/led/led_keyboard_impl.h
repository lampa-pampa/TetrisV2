#ifndef INCLUDE_UI_LED_KEYBOARD_IMPL
#define INCLUDE_UI_LED_KEYBOARD_IMPL

#include "ui/keyboard/keyboard.h"

#include <deque>
#include <vector>

#include "config/keyboard/led/config.h"

namespace Tetris::Ui
{

class LedKeyboardImpl final: public Keyboard
{
public:
    LedKeyboardImpl(const KeyboardConfig& config);

    int get_pressed_key_code() override;

private:
    const KeyboardConfig& config_;
    std::vector<std::vector<bool>> key_states_;
    std::deque<int> pressed_keys_;

    void setup_pin_modes();
    void update_key_states();
    void update_keys_row_state(int y);
    void update_key_state(int x, int y, bool new_state);

    int create_key_code(int x, int y) const
    {
        const std::size_t key_index{config_.column_pins.size() * y + x};
        return config_.key_index_to_key_code.at(key_index);
    }
};

} // namespace Tetris::Ui

#endif
