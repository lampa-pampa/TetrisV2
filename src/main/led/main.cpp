#include "config/filled_config.h"
#include "config/keyboard/led/filled_config.h"
#include "config/matrix_display/led/filled_config.h"
#include "run_tetris/run_tetris.h"
#include "ui/keyboard/led/led_keyboard_impl.h"
#include "ui/matrix_display/led/led_matrix_display_impl.h"

using Tetris::config;
using Tetris::keyboard_config;
using Tetris::matrix_display_config;
using Tetris::run_tetris;
using Tetris::Ui::LedKeyboardImpl;
using Tetris::Ui::LedMatrixDisplayImpl;

void setup()
{
    while (true)
    {
        LedMatrixDisplayImpl matrix{matrix_display_config};
        LedKeyboardImpl keyboard{keyboard_config};
        run_tetris(config, keyboard, matrix);
    }
}

void loop() {}
