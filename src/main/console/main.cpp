#include "config/filled_config.h"
#include "config/matrix_display/console/filled_matrix_config.h"
#include "run_tetris/run_tetris.h"
#include "ui/input_receiver/console/console_input_receiver_impl.h"
#include "ui/matrix_display/console/console_matrix_display_impl.h"

using Tetris::config;
using Tetris::matrix_config;
using Tetris::run_tetris;
using Tetris::Ui::ConsoleInputReceiverImpl;
using Tetris::Ui::ConsoleMatrixDisplayImpl;

int main()
{
    ConsoleMatrixDisplayImpl matrix_display{matrix_config};
    ConsoleInputReceiverImpl input_receiver{matrix_display.get_window()};
    
    run_tetris(config, input_receiver, matrix_display);

    return 0;
}