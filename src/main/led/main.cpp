#include "config/filled_config.h"
#include "config/matrix_display/led/filled_matrix_config.h"
#include "config/input_receiver/led/filled_input_config.h"
#include "run_tetris/run_tetris.h"
#include "ui/input_receiver/led/led_input_receiver_impl.h"
#include "ui/matrix_display/led/led_matrix_display_impl.h"

using Tetris::config;
using Tetris::matrix_config;
using Tetris::input_config;
using Tetris::run_tetris;
using Tetris::Ui::LedInputReceiverImpl;
using Tetris::Ui::LedMatrixDisplayImpl;

void setup()
{
    LedMatrixDisplayImpl matrix{matrix_config};
    LedInputReceiverImpl input_receiver{input_config};

    run_tetris(config, input_receiver, matrix);
}

void loop() {}