#include "config/filled_config.h"
#include "run_tetris/run_tetris.h"
#include "ui/input_receiver/console/console_input_receiver_impl.h"
#include "ui/matrix_display/console/console_matrix_display_impl.h"

using Tetris::Ui::ConsoleMatrixDisplayImpl;
using Tetris::Ui::ConsoleInputReceiverImpl;
using Tetris::config;
using Tetris::run_tetris;

int main()
{
    ConsoleMatrixDisplayImpl matrix{
        config.ui.matrix.size,
        {2, 1},
        0xff,
        {
            L' ',
            L'·',
            L'◦',
            L'◌',
            L'○',
            L'◎',
            L'◉',
            L'●',
        },
        {config.ui.matrix.color_id_to_matrix_color},
    };

    ConsoleInputReceiverImpl input_receiver{
        matrix.get_window()
    };

    run_tetris(
        config,
        input_receiver,
        matrix
    );

    return 0;
}