#ifndef INCLUDE_CREATE_GAME_CONTROLLER_H
#define INCLUDE_CREATE_GAME_CONTROLLER_H

#include "config/config.h"
#include "ui/keyboard/keyboard.h"
#include "ui/matrix_display/matrix_display.h"

namespace Tetris
{

void run_tetris(const Config& config,
    Ui::Keyboard& keyboard,
    Ui::MatrixDisplay& matrix_display);

}

#endif
