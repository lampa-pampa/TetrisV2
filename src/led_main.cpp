#include "config/filled_config.h"
#include "run_tetris/run_tetris.h"
#include "ui/input_receiver/led/led_input_receiver_impl.h"
#include "ui/matrix_display/led/led_matrix_display_impl.h"

using Tetris::Ui::LedMatrixDisplayImpl;
using Tetris::Ui::LedInputReceiverImpl;
using Tetris::config;
using Tetris::run_tetris;

int main()
{
    LedMatrixDisplayImpl matrix{
        {config.ui.matrix.size},
        160,
        1,
        {
            25,
            26,
            27,
            14,
            12,
            13,
            23,
            19,
            5,
            17,
            33,
            4,
            18,
            16,
        },
        config.ui.matrix.color_id_to_matrix_color,
    };

    LedInputReceiverImpl input_receiver{};

    run_tetris(
        config,
        input_receiver,
        matrix
    );

    return 0;
}