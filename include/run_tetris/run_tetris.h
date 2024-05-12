#ifndef INCLUDE_CREATE_GAME_CONTROLLER_H
#define INCLUDE_CREATE_GAME_CONTROLLER_H

#include "config/config.h"
#include "ui/input_receiver/input_receiver.h"
#include "ui/matrix_display/matrix_display.h"

namespace Tetris
{

void run_tetris(
    const Config& config,
    Ui::InputReceiver& input_receiver,
    Ui::MatrixDisplay& matrix_display
);

}

#endif