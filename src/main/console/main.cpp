#include "config/filled_config.h"
#include "config/keyboard/console/filled_config.h"
#include "config/matrix_display/console/filled_config.h"
#include "rng/console/console_rng_impl.h"
#include "run_tetris/run_tetris.h"
#include "ui/keyboard/console/console_keyboard_impl.h"
#include "ui/matrix_display/console/console_matrix_display_impl.h"

using Tetris::config;
using Tetris::ConsoleRngImpl;
using Tetris::run_tetris;
using Tetris::Ui::ConsoleKeyboardImpl;
using Tetris::Ui::ConsoleMatrixDisplayImpl;
using Tetris::Ui::keyboard_config;
using Tetris::Ui::matrix_display_config;

int main()
{
    while (true)
    {
        ConsoleMatrixDisplayImpl matrix_display{matrix_display_config};
        ConsoleKeyboardImpl keyboard{
            matrix_display.get_window(), keyboard_config};
        ConsoleRngImpl rng{};
        run_tetris(config, keyboard, matrix_display, rng);
    }
}
