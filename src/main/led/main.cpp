#include "config/filled_config.h"
#include "config/keyboard/led/filled_config.h"
#include "config/matrix_display/led/filled_config.h"
#include "rng/led/led_rng_impl.h"
#include "run_tetris/run_tetris.h"
#include "ui/keyboard/led/led_keyboard_impl.h"
#include "ui/matrix_display/led/led_matrix_display_impl.h"

using Tetris::config;
using Tetris::LedRngImpl;
using Tetris::run_tetris;
using Tetris::Ui::keyboard_config;
using Tetris::Ui::LedKeyboardImpl;
using Tetris::Ui::LedMatrixDisplayImpl;
using Tetris::Ui::matrix_display_config;

void setup()
{
    while (true)
    {
        LedMatrixDisplayImpl matrix{matrix_display_config};
        LedKeyboardImpl keyboard{keyboard_config};
        LedRngImpl rng{3};
        run_tetris(config, keyboard, matrix, rng);
    }
}

void loop() {}
