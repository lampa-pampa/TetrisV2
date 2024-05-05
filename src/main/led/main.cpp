#include "config/filled_config.h"
#include "run_tetris/run_tetris.h"
#include "ui/input_receiver/led/led_input_receiver_impl.h"
#include "ui/matrix_display/led/config/filled_matrix_config.h"
#include "ui/matrix_display/led/led_matrix_display_impl.h"

using Tetris::config;
using Tetris::matrix_config;
using Tetris::run_tetris;
using Tetris::Ui::LedInputReceiverImpl;
using Tetris::Ui::LedMatrixDisplayImpl;

void setup()
{
    LedMatrixDisplayImpl matrix{matrix_config};

    LedInputReceiverImpl input_receiver{};

    run_tetris(
        config,
        input_receiver,
        matrix
    );
}

void loop() {}