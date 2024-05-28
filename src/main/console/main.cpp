#include "config/filled_config.h"
#include "config/matrix_display/console/filled_config.h"
#include "run_tetris/run_tetris.h"
#include "ui/keyboard/console/console_keyboard_impl.h"
#include "ui/matrix_display/console/console_matrix_display_impl.h"

using Tetris::config;
using Tetris::matrix_display_config;
using Tetris::run_tetris;
using Tetris::Ui::ConsoleKeyboardImpl;
using Tetris::Ui::ConsoleMatrixDisplayImpl;

int main()
{
    while(true)
    {
        ConsoleMatrixDisplayImpl matrix_display{matrix_display_config};
        ConsoleKeyboardImpl keyboard{matrix_display.get_window()};
        
        run_tetris(config, keyboard, matrix_display);
    }
}